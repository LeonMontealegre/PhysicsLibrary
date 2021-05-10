
declare global {
    interface Array<T> {
        with: <T2>(f: (v: T2, i: number) => T2) => Array<T2>;
    }
    interface ArrayConstructor {
        zip: <T1, T2>(arr1: T1[], arr2: T2[]) => [T1, T2][];
    }
}

Array.prototype.with = function<T2>(f: (v: T2, i: number) => T2) {
    return new Array(this.length).fill(undefined).map(f);
}

Array.zip = function<T1, T2>(arr1: T1[], arr2: T2[]) {
    return arr1.map((v1, i) => [v1, arr2[i]]);
}

export {};
