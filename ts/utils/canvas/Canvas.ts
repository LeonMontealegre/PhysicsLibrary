import {V} from "Vector";

import {Painter} from "./Painter";
import {CanvasPainter} from "./CanvasPainter";

export class Canvas {
    public canvas: HTMLCanvasElement;
    public painter: Painter;

    private drawFunc: (p: Painter) => void;
    private onResizeCallback: () => void;

    public constructor(id: string,
                       drawFunc: (p: Painter) => void,
                       onResize: () => void = () => { this.draw(); }) {
        this.drawFunc = drawFunc;
        this.onResizeCallback = onResize;

        this.canvas = document.getElementById(id) as HTMLCanvasElement;
        this.painter = new CanvasPainter(this.canvas);

        window.addEventListener("resize", () => this.onResize(), false);
        this.onResize();
    }

    public draw(): void {
        this.painter.save();

        this.painter.clear();

        this.painter.translate(V(this.canvas.width/2, this.canvas.height/2));
        this.painter.scale(V(1, -1));

        this.drawFunc(this.painter);

        this.painter.restore();
    }

    public createImageData(w: number, h: number): ImageData {
        return this.painter.createImageData(w, h);
    }

    public onResize() {
        this.canvas.width = window.innerWidth;
        this.canvas.height = window.innerHeight;

        this.onResizeCallback();
    }

    public get width(): number {
        return this.canvas.width;
    }

    public get height(): number {
        return this.canvas.height;
    }
}
