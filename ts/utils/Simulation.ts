import {Painter} from "canvas/Painter";
import {Canvas} from "canvas/Canvas";

export class Simulation<T extends Record<string, any>> {
    private simReducer: (sim?: T, change?: Partial<T>) => T;
    private stepFunc: (sim: T) => void;

    private sim: T;

    private canvas: Canvas;

    private stopped: boolean;

    public constructor(canvasId: string,
                       simReducer: (sim?: T, change?: Partial<T>) => T,
                       stepFunc: (sim: T) => void,
                       drawFunc: (p: Painter, sim: T) => void) {
        this.simReducer = simReducer;
        this.stepFunc = stepFunc;

        this.sim = simReducer();

        this.canvas = new Canvas(canvasId, (p) => drawFunc(p, this.sim));

        this.stopped = true;
    }

    public reset(): void {
        this.stopped = true;
        this.sim = this.simReducer(); // Gets initial state
        this.canvas.draw();
    }

    public step(): void {
        this.stepFunc(this.sim);
        this.canvas.draw();

        if (!this.stopped)
            requestAnimationFrame(() => this.step());
    }

    public onSimChange(change?: Partial<T>): T {
        this.sim = this.simReducer(this.sim, change);
        this.canvas.draw(); // Redraw after change
        return this.sim;
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
