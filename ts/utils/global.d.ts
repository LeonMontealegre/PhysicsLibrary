
declare module "*.cpp" {
    import {WASMModule} from "./WASM";
    export default function(): Promise<WASMModule>;
}
