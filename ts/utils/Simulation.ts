import {Painter} from "canvas/Painter";
import {Canvas} from "canvas/Canvas";

export class Simulation<T extends Record<string, any>> {
    private canvas: Canvas;
    private simReducer: (sim?: T, change?: Partial<T>) => T;
    private stepFunc: (sim: T) => void;

    private sim: T;

    private stopped: boolean;

    public constructor(canvasId: string,
                       simReducer: (sim?: T, change?: Partial<T>) => T,
                       stepFunc: (sim: T) => void,
                       drawFunc: (p: Painter, sim: T) => void) {
        this.canvas = new Canvas(canvasId, (p) => drawFunc(p, this.sim));
        this.simReducer = simReducer;
        this.stepFunc = stepFunc;
        this.sim = simReducer();
        this.stopped = true;
    }

    public step(): void {
        this.stepFunc(this.sim);
        this.canvas.draw();

        if (!this.stopped)
            requestAnimationFrame(() => this.step());
    }

    public onSimChange(change?: Partial<T>): T {
        return (this.sim = this.simReducer(this.sim, change));
    }

    public start() {
        this.stopped = false;
        requestAnimationFrame(() => this.step());
    }

    public stop() {
        this.stopped = true;
    }

    public getSim(): T {
        return this.sim;
    }

    public isStopped(): boolean {
        return this.stopped;
    }

}
