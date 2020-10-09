import {Painter} from "canvas/Painter";
import {Canvas} from "canvas/Canvas";

export class Simulation {
    private canvas: Canvas;
    private stepFunc: () => void;

    private stopped: boolean;

    public constructor(canvasId: string,
                       stepFunc: () => void,
                       drawFunc: (p: Painter) => void) {
        this.canvas = new Canvas(canvasId, drawFunc);
        this.stepFunc = stepFunc;
        this.stopped = true;
    }

    private step(): void {
        this.stepFunc();

        if (!this.stopped)
            requestAnimationFrame(() => this.step());
    }

    public start() {
        this.stopped = false;
        requestAnimationFrame(() => this.step());
    }

    public stop() {
        this.stopped = true;
    }

    public isStopped(): boolean {
        return this.stopped;
    }

}