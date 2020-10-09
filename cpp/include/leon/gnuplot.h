#ifndef __GNUPLOT_H__
#define __GNUPLOT_H__

#include <stdlib.h>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "utils.h"
#include "matrix.h"
#include "vector.h"

enum TitlePosition {
    TOP,
    BOTTOM
};

enum PointType {
    SMALL_DOT,
    PLUS,
    X,
    X_STAR,
    RECT,
    FILLED_RECT,
    CIRC,
    FILLED_CIRC,
    TRI,
    FILLED_TRI,
    U_TRI,
    FILLED_U_TRI,
    DIAMOND,
    FILLED_DIAMOND,
    PENTAGON,
    FILLED_PENTAGON
};

struct TitleOptions {
    std::string label;
    TitlePosition pos;
    int fontSize;
};

struct AxisOptions {
    std::string label;
    int fontSize;
    bool log;
    bool autoScale;
    double a, b;
};

enum PlotStyleType {
    Default, Hist
};

struct PlotStyle {
    std::string type, color, palette;
    int lineType, pointType, bins;
    float lineWidth, pointSize, boxWidth, solid;
    bool border, transparent, isColorHex;

    PlotStyle(std::string type_, std::string color_ = "",
              int lineType_ = 1, int pointType_ = 1,
              float lineWidth_ = 1, float pointSize_ = 1):
            type(type_), color(color_),
            lineType(lineType_), pointType(pointType_),
            lineWidth(lineWidth_), pointSize(pointSize_), border(true) {
                isColorHex = (color_.empty() ? false : color_[0] == '#');
            }
    PlotStyle(int bins_, float boxWidth_ = 1,
              float solid_ = 1, std::string color_ = "",
              int lineType_ = 1, float lineWidth_ = 1):
            PlotStyle("boxes", color_, lineType_, 0, lineWidth_, 0) {
                bins = bins_; boxWidth = boxWidth_; solid = solid_;
                transparent = solid_ < 1;
                border = (lineWidth > 0);
            }
    PlotStyle(float radius_, float solid_ = 1,
              std::string color_ = "", int lineType_ = 1, float lineWidth_ = 1):
            PlotStyle("circles", color_, lineType_, 0, lineWidth_, radius_) {
                solid = solid_;
                transparent = solid_ < 1;
                border = (lineWidth > 0);
            }
    PlotStyle(float radius_, std::string color_ = "", int pointType_ = 1):
            PlotStyle("points", color_, 0, pointType_, 0, radius_) {
            }
};
PlotStyle CircleStyle(float radius, float solid = 1,
                      std::string color = "rgb '#000000'",
                      int lineType = 1, float lineWidth = 1) {
    return {radius, solid, color, lineType, lineWidth};
}
PlotStyle PointStyle(float radius, std::string color = "", int pointType = 1) {
    return {radius, color, pointType};
}
PlotStyle HistStyle(int bins, float boxWidth = 1,
                    float solid = 1, std::string color = "rgb '#000000'",
                    int lineType = 1, float lineWidth = 1) {
    return {bins, boxWidth, solid, color, lineType, lineWidth};
}
PlotStyle MapStyle(std::string palette = "color") {
    PlotStyle style("");
    style.palette = palette;
    return style;
}

struct DataBlock {
    int z;
    std::string label;
    PlotStyle style;
    std::vector<std::vector<double>> data;
};


// ***************************
// ***************************
// ***************************
//
// TODO: maybe make a PyPlot?
//
// ***************************
// ***************************
// ***************************
class GNUPlot {
public:
    // GNUPlot() {

    // }
    GNUPlot(const std::string& title_, const std::vector<std::string> axes_) {
        title = {title_, TitlePosition::TOP, 14};

        // create axes
        for (uint i = 0; i < axes_.size(); i++) {
            axes.push_back({
                axes_[i],
                14, false, true,
                0, 0
            });
        }

        width = 640;
        height = 480;

        animated = false;
        splot = false;
    }

    void execute(const std::string& outFile, const std::string& customDataFile = "") const {
        export_data(customDataFile);

        std::string cmd = get_command(customDataFile);
        std::string command = BASE_COMMAND + "\"" + cmd + "\"" + " > " + outFile + (animated ? ".gif" : ".jpeg");
        std::cout << "COMMAND: \n" << command << std::endl;
        int x = system(command.c_str());
        std::cout << x << std::endl;
        if (x == -1) {
            std::cerr << "Failed to execute command!" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (customDataFile.empty() && remove(TEMP_DATA_FILE.c_str()) != 0)
            std::cerr << "Failed to remove temporary data file!" << std::endl;
    }

    void set_animated(uint delay_ = 100) {
        animated = true;
        delay = delay_;
    }

    uint add_data_block(const std::string& label = "", PlotStyle style = {"lines"}, int z = 0) {
        data.push_back({z, label, style});
        return data.size() - 1;
    }

    template<uint N>
    void add_data(uint block, const Vector<N, double>& v) {
        std::vector<double> row;
        for (uint i = 0; i < N; i++)
            row.push_back(v[i]);
        data[block].data.push_back(row);
    }
    void add_data(uint block, std::initializer_list<double> li) {
        data[block].data.push_back(li);
    }
    void add_data(std::initializer_list<double> li) {
        data[data.size()-1].data.push_back(li);
    }
    template<uint N, uint M>
    void add_grid(const Matrix<N,M>& m, const PlotStyle& style) {
        if (!pm3d) {
            std::cerr << "Can only add grid for pm3d-type plot! Call .set_pm3d() first!" << std::endl;
            exit(1);
        }
        for (uint i = 0; i < N; i++) {
            uint b = add_data_block("", style);
            for (uint j = 0; j < M; j++)
                add_data(b, {(double)i, (double)j, m[i][j]});
        }
    }

    void set_size(int w, int h) {
        width = w;
        height = h;
    }

    void set_3d() {
        splot = true;
    }
    void set_pm3d() {
        pm3d = true;
    }

    void set_axis_log(int axis, bool log = true) {
        axes[axis].log = log;
    }

    void set_axis_auto(int axis, bool autoScale = true) {
        axes[axis].autoScale = autoScale;
    }

    void set_axis_range(int axis, double a, double b) {
        axes[axis].a = a;
        axes[axis].b = b;
        axes[axis].autoScale = false;
    }

private:
    static const std::string BASE_COMMAND;
    static const std::string TEMP_DATA_FILE;

    TitleOptions title;
    std::vector<AxisOptions> axes;

    std::vector<DataBlock> data;

    int width, height;

    bool animated, splot, pm3d;
    uint delay;

    void export_data(const std::string& dataFile = "") const {
        static const auto DATA_SEPARATOR = " ";

        std::ofstream file(dataFile.empty() ? TEMP_DATA_FILE : dataFile);

        // Get sorted data
        std::vector<DataBlock> data2 = data;
        std::sort(data2.begin(), data2.end(), [](const DataBlock& a, const DataBlock& b) -> bool { return a.z < b.z; });

        for (uint i = 0; i < data2.size(); i++) {
            file << "\"" << data2[i].label << "\"" << "\n";
            for (uint j = 0; j < data2[i].data.size(); j++) {
                for (uint k = 0; k < data2[i].data[j].size(); k++) {
                    file << data2[i].data[j][k];
                    if (k != data2[i].data[j].size() - 1)
                        file << DATA_SEPARATOR;
                }
                file << "\n";
            }
            if (i != data2.size() - 1)
                file << "\n\n";
        }

        file.close();
    }

    double find_min(uint block, uint axes) const {
        return *std::min_element(data[block].data[axes].begin(), data[block].data[axes].end());
    }

    double find_max(uint block, uint axes) const {
        return *std::max_element(data[block].data[axes].begin(), data[block].data[axes].end());
    }

    std::string get_command(const std::string& dataFile = "") const {
        static const auto SEPARATOR = ";";
        const std::string AXES_NAMES[3] = {"x", "y", "z"};

        std::stringstream str;

        if (animated) {
            str << "set terminal gif animate delay " << delay << " size " << width << "," << height << SEPARATOR;
        } else {
            str << "set terminal jpeg size " << width << "," << height << SEPARATOR;
        }

        if (title.pos == TOP) {
            str << "set title '" << title.label << "' font " << "'," << title.fontSize << "'" << SEPARATOR;
        } else if (title.pos == BOTTOM) {
            str << "set label 11 center at graph 0.5,char 1 '" << title.label << "' font " << "'," << title.fontSize << "'" << SEPARATOR;
            str << "set bmargin 5" << SEPARATOR;
        }

        if (pm3d)
            str << "set pm3d" << SEPARATOR;

        // Axis
        for (uint i = 0; i < axes.size(); i++) {
            str << "set " << AXES_NAMES[i] << "label '" << axes[i].label << "' font '," << axes[i].fontSize << "'" << SEPARATOR;
            if (axes[i].log)
                str << "set logscale " << (AXES_NAMES[i] == "z" && pm3d ? "zcb" : AXES_NAMES[i]) << SEPARATOR;
            if (axes[i].autoScale)
                str << "set autoscale " << AXES_NAMES[i] << "fix" << SEPARATOR;
            if (!axes[i].autoScale && axes[i].a != axes[i].b)
                str << "set " << (AXES_NAMES[i] == "z" && pm3d ? "cb" : AXES_NAMES[i]) << "range " << "[" << axes[i].a << ":" << axes[i].b << "]" << SEPARATOR;
        }

        std::vector<DataBlock> data2 = data;
        std::sort(data2.begin(), data2.end(), [](const DataBlock& a, const DataBlock& b) -> bool { return a.z < b.z; });

        if (pm3d) {
            str << "set palette " << data2[0].style.palette << SEPARATOR;
            str << "plot" << "'./" << (dataFile.empty() ? TEMP_DATA_FILE : dataFile) << "' with image title columnheader(1)" << SEPARATOR;
            return str.str();
        }


        // Create styles
        bool first_hist = true;
        for (uint i = 0; i < data2.size(); i++) {
            const PlotStyle& style = data2[i].style;

            if (!style.color.empty()) {
                str << "set style line " << (i+1) << " ";
                str << "linecolor rgb " << (style.isColorHex ? "'" : "") << style.color << (style.isColorHex ? "'" : "") << " ";
                str << "linetype " << style.lineType << " linewidth " << style.lineWidth << " ";
                str << "pointtype " << style.pointType << " pointsize " << style.pointSize << SEPARATOR;
            }
            if (style.type == "boxes") {
                if (first_hist) {
                    str << "hist(x,width)=width*floor(x/width)+width/2.0" << SEPARATOR;
                    first_hist = false;
                }
                double max = (axes[0].autoScale ? find_max(i, 0) : axes[0].b);
                double min = (axes[0].autoScale ? find_min(i, 0) : axes[0].a);
                double width = (max - min) / style.bins;
                str << "set boxwidth " << style.boxWidth*width << SEPARATOR;
            }
        }

        // Plots
        str << (splot ? "s" : "") << "plot ";
        for (uint i = 0; i < data2.size(); i++) {
            const PlotStyle& style = data2[i].style;

            str << "'./" << (dataFile.empty() ? TEMP_DATA_FILE : dataFile) << "' index " << i;
            if (style.type == "boxes") {
                double max = (axes[0].autoScale ? find_max(i, 0) : axes[0].b);
                double min = (axes[0].autoScale ? find_min(i, 0) : axes[0].a);
                double width = (max - min) / style.bins;
                str << " u (hist(\\$1," << width << ")):(1.0) smooth freq";
            }
            else if (style.type == "circles") {
                str << " u 1:2:(" << style.pointSize/2 << ")";
            }
            else if (style.type == "paths") {
                str << " u 1:2:(\\$3-\\$1):(\\$4-\\$2) with vectors nohead";
            }
            if (style.type != "paths") {
                str << " w " << style.type;
            }
            if (style.type == "boxes" || style.type == "circles") {
                str << " fill" << (style.transparent ? " transparent" : "") << " solid " << style.solid << (style.border ? " border" : " noborder");
            }
            if (!style.color.empty()) // only add linestyle if there's a color
                str << " linestyle " << (i+1);
            str << " title columnheader(1)";

            if (animated)
                str << SEPARATOR << (i == data2.size()-1 ? "" : (splot ? "splot " : "plot "));
            else
                str << (i == data2.size()-1 ? SEPARATOR : ", ");
        }

        return str.str();
    }
};

const std::string GNUPlot::TEMP_DATA_FILE = ".__TEMP_DATA_GNUPLOT__.dat";
const std::string GNUPlot::BASE_COMMAND = "gnuplot -e ";

#endif