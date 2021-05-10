import {Vector} from "Vector";
import {Grid} from "utils/Grid";

type CapType = "butt" | "round" | "square";
export class LineStyle {
    public color: string;
    public width: number;
    public cap: CapType;

    public constructor(color: string, width: number, cap: CapType) {
        this.color = color;
        this.width = width;
        this.cap = cap;
    }
}

export interface Painter {
    translate(p: Vector): void;
    rotateAbout(a: number, v: Vector): void;
    scale(s: Vector): void;
    scaleAbout(s: Vector, v: Vector): void;

    save(): void;
    restore(): void;

    clear(): void;

    drawLine(a: Vector, b: Vector): void;
    drawCurve(p1: Vector, p2: Vector, c1: Vector, c2: Vector): void;

    drawArrow(a: Vector, b: Vector, options?: {
        len?: number,
        angle?: number,
        arrowStrokeStyle?: LineStyle,
        lineStrokeStyle?: LineStyle
    }): void;

    drawGrid<T extends {id: string}>(
        grid: Grid<T>,
        styleCell: (val: T, pos: number[]) => {
            fillStyle?: string;
            strokeStyle?: string;
        },
        options?: {
            cellWidth?: number;
            cellHeight?: number;
        }
    ): void;

    drawText(text: string, pos: Vector): void;

    strokeRect(pos: Vector, size: Vector): void;

    fillRect(pos: Vector, size: Vector): void;
    fillCirc(pos: Vector, radius: number): void;

    createImageData(w: number, h: number): ImageData;
    putImageData(data: ImageData, dx: number, dy: number): void;

    setStrokeColor(col: string): void;
    setFillColor(col: string): void;

    setLineStyle(style: LineStyle): void;
    setAlpha(alpha: number): void;
}
