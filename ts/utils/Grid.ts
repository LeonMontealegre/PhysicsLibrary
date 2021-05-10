
export class Grid<T> {
    private dims: number[];
    private data: T[];

    private boundaryHandler?: (grid: Grid<T>, pos: number[]) => T;

    public constructor(dims: number[], boundaryHandler?: (grid: Grid<T>, pos: number[]) => T) {
        this.dims = dims;
        this.data = new Array(this.dims.reduce((p, c) => p*c, 1)).fill(undefined);
        this.boundaryHandler = boundaryHandler;
    }

    public set(val: T, ...pos: number[]): Grid<T> {
        if (!this.isInBounds(...pos))
            throw new Error(`Can't set value on grid that's out of bounds! (${pos.join(",")})`);
        this.data[this.getIndex(pos)] = val;
        return this;
    }

    public get(...pos: number[]): T {
        if (!this.isInBounds(...pos))
            return this.boundaryHandler!(this, pos);
        return this.data[this.getIndex(pos)];
    }

    public getIndex(pos: number[]): number {
        if (pos.length !== this.dims.length)
            throw new Error(`Received position of dimension ${pos.length} for grid of dimension ${this.dims.length}!`);
        return Array.zip(pos, this.dims)
            .reverse()
            .reduce((p, [i, d]) => (p * d + i), 0);
    }

    public getPos(i: number): number[] {
        return this.dims.map((d) => {
            const val = i % d;
            i = Math.floor(i / d);
            return val;
        })
    }

    public replaceWith(other: Grid<T>): Grid<T> {
        if (other.dims.length !== this.dims.length)
            throw new Error(`Cannot replace grid with ${this.dims.length} dimensions with grid with ${other.dims.length} dimensions!`);
        if (other.dims.some((d, i) => d != this.dims[i]))
            throw new Error(`Cannot replace grid with dimensions [${this.dims.join(" ")}] with grid with dimensions [${other.dims.join(" ")}]!`);
        this.data = other.data.slice();
        return this;
    }

    public fill(f: (curVal: T, pos: number[]) => T): Grid<T> {
        this.iterate((v, p) => {
            this.set(f(v, p), ...p);
        });
        return this;
    }

    public iterate(f: (val: T, pos: number[]) => void): Grid<T> {
        for (let i = 0; i < this.data.length; i++)
            f(this.data[i], this.getPos(i));
        return this;
    }

    public map(f: (curVal: T, pos: number[]) => T): Grid<T> {
        const grid = new Grid<T>(this.dims, this.boundaryHandler);
        this.iterate((v, p) => {
            grid.set(f(v, p), ...p);
        });
        return grid;
    }

    public isInBounds(...pos: number[]): boolean {
        return pos.every((indx, i) => indx >= 0 && indx < this.dims[i]);
    }

    public getSize(dim: number): number {
        return this.dims[dim];
    }

    public getDimension(): number {
        return this.dims.length;
    }

}
