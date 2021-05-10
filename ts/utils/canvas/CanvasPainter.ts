import {V, Vector} from "Vector";
import {Grid} from "utils/Grid";

import {Painter, LineStyle} from "./Painter";

export class CanvasPainter implements Painter {
    private canvas: HTMLCanvasElement;
    private ctx: CanvasRenderingContext2D;

    public constructor(canvas: HTMLCanvasElement) {
        this.canvas = canvas;
        this.ctx = canvas.getContext("2d")!;
    }

    public translate(p: Vector): void {
        this.ctx.translate(p.x, p.y);

        this.ctx.getTransform().multiply();
    }

    public rotateAbout(a: number, v: Vector): void {
        this.translate(v);
        this.ctx.rotate(a);
        this.translate(v.scale(-1));
    }

    public scaleAbout(s: Vector, v: Vector): void {
        this.translate(v);
        this.scale(s);
        this.translate(v.scale(-1));
    }

    public scale(s: Vector): void {
        this.ctx.scale(s.x, s.y);
    }

    public save(): void {
        this.ctx.save();
    }

    public restore(): void {
        this.ctx.restore();
    }

    public clear(): void {
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }

    public strokeRect(pos: Vector, size: Vector): void {
        this.ctx.strokeRect(pos.x, pos.y, size.x, size.y);
    }

    public fillRect(pos: Vector, size: Vector): void {
        this.ctx.fillRect(pos.x, pos.y, size.x, size.y);
    }

    public fillCirc(pos: Vector, radius: number): void {
        this.ctx.beginPath();
        this.ctx.arc(pos.x, pos.y, radius, 0, 2*Math.PI);
        this.ctx.fill();
        this.ctx.closePath();
    }

    public drawLine(a: Vector, b: Vector): void {
        this.ctx.beginPath();
        this.ctx.moveTo(a.x, a.y);
        this.ctx.lineTo(b.x, b.y);
        this.ctx.stroke();
        this.ctx.closePath();
    }

    public drawCurve(p1: Vector, p2: Vector, c1: Vector, c2: Vector): void {
        this.ctx.beginPath();
        this.ctx.moveTo(p1.x, p1.y);
        this.ctx.bezierCurveTo(c1.x, c1.y, c2.x, c2.y, p2.x, p2.y);
        this.ctx.stroke();
        this.ctx.closePath();
    }

    public drawArrow(a: Vector, b: Vector, options?: {
        len?: number,
        angle?: number,
        arrowStrokeStyle?: LineStyle,
        lineStrokeStyle?: LineStyle
    }): void {
        const arrowLen = options?.len ?? 3;
        const arrowAngle = options?.angle ?? Math.PI/6;
        const arrowStyle = options?.arrowStrokeStyle;
        const lineStyle = options?.lineStrokeStyle;

        const angle = b.sub(a).angle();

        this.ctx.beginPath();

        if (lineStyle)
            this.setLineStyle(lineStyle);
        this.ctx.moveTo(a.x, a.y);
        this.ctx.lineTo(b.x, b.y);

        if (arrowStyle)
            this.setLineStyle(arrowStyle);
        // arrow head
        this.ctx.lineTo(b.x - arrowLen*Math.cos(angle - arrowAngle), b.y - arrowLen*Math.sin(angle - arrowAngle));
        this.ctx.moveTo(b.x, b.y);
        this.ctx.lineTo(b.x - arrowLen*Math.cos(angle + arrowAngle), b.y - arrowLen*Math.sin(angle + arrowAngle));

        this.ctx.stroke();
        this.ctx.closePath();
    }

    public drawGrid<T extends {id: string}>(
        grid: Grid<T>,
        styleCell: (val: T, pos: number[]) => {
            fillStyle?: string;
            strokeStyle?: string;
        },
        options?: {
            cellWidth?: number;
            cellHeight?: number;
        }) {
        if (grid.getDimension() !== 2)
            throw new Error(`Unsupported grid dimension ${grid.getDimension()} for "drawGrid"!`);

        const {cellWidth, cellHeight} = options ?? {};
        const w = cellWidth ??  0; // TODO: Auto-detect using screen size
        const h = cellHeight ?? 0; // TODO: Auto-detect using screen size

        grid.iterate((v, [r, c]) => {
            const {fillStyle, strokeStyle} = styleCell(v, [r, c]);

            // draw cell
            const x = c * w - w*grid.getSize(1)/2;
            const y = r * h - w*grid.getSize(0)/2;

            if (fillStyle) {
                this.setFillColor(fillStyle);
                this.fillRect(V(x, y), V(w, h))
            }
            if (strokeStyle) {
                this.setStrokeColor(strokeStyle);
                this.strokeRect(V(x, y), V(w, h));
            }
        })
    }

    public drawText(text: string, pos: Vector): void {
        this.ctx.fillText(text, pos.x, pos.y);
    }

    public createImageData(w: number, h: number): ImageData {
        return this.ctx.createImageData(w, h);
    }

    public putImageData(data: ImageData, dx: number = 0, dy: number = 0): void {
        this.ctx.putImageData(data, dx, dy);
    }

    public setStrokeColor(col: string): void {
        this.ctx.strokeStyle = col;
    }
    public setFillColor(col: string): void {
        this.ctx.fillStyle = col;
    }

    public setLineStyle(style: LineStyle): void {
        this.ctx.strokeStyle = style.color;
        this.ctx.lineWidth = style.width;
        this.ctx.lineCap = style.cap;
    }
    public setAlpha(alpha: number): void {
        this.ctx.globalAlpha = alpha;
    }

}
