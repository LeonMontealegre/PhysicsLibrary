
export type WASMModule = {
    _malloc: (length: number) => number;
    _free: (array: number) => void;
    HEAPF64: Float64Array;
}

export const WASMInstance = (module: WASMModule) => ({
    create_array: (arr: number[]) => {
        const res = new Float64Array(arr);

        const arrPointer = module._malloc(res.length * Float64Array.BYTES_PER_ELEMENT);
        module.HEAPF64.set(res, arrPointer / Float64Array.BYTES_PER_ELEMENT);

        return arrPointer;
    },
    free_array: (arr: number) => {
        module._free(arr);
    }
});
