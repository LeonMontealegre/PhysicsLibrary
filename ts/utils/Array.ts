
declare global {
    interface Array<T> {
        with: <T2>(f: (v: T2, i: number) => T2) => Array<T2>;
    }
    interface ArrayConstructor {
        zip: <T extends Array<any>>(...arrs: { [K in keyof T]: Array<T[K]> }) => T[];
    }
}


Array.prototype.with = function<T2>(f: (v: T2, i: number) => T2) {
    return new Array(this.length).fill(undefined).map(f);
}

Array.zip = function<T extends Array<any>>(...arrs: { [K in keyof T]: Array<T[K]> }) {
    return new Array(Math.min(...arrs.map(arr => arr.length)))
        .fill(undefined)
        .map((_, i) => arrs.map(arr => arr[i])) as T;
}

export {};
