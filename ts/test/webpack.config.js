const ts = require("typescript");
const path = require("path");

const HtmlWebpackPlugin = require("html-webpack-plugin");

function getAliases(cwd) {
    const file = path.join(cwd, "tsconfig.json");

    const rawConfig = ts.readConfigFile(file, ts.sys.readFile).config;
    const config = ts.parseJsonConfigFileContent(
        rawConfig,
        ts.sys,
        cwd
    );

    let aliases = {};
    if (config.options.paths) {
        const paths = config.options.paths;
        Object.entries(paths).forEach(([n, [p]]) => {
            const name = n.replace("/*", "");
            const url = path.resolve(cwd, p.replace("/*", ""));
            aliases[name] = url;
        });
    }

    return aliases;
}

const cwd = process.cwd();

module.exports = {
    mode: "development",
    entry: path.join(cwd, "."),
    output: {
        path: path.join(cwd, "build/"),
        // publicPath: config.publicPath,
        filename: "bundle.js"
    },
    module: {
        rules: [
            { test: /\.(ts)$/, loader: "ts-loader" }
        ]
    },
    resolve: {
        alias: getAliases(cwd),
        extensions: [".ts", ".js"]
    },
    plugins: [
        new HtmlWebpackPlugin({ template: path.join(cwd, "index.html") })
    ]
}
