import {V} from "Vector";
import {Simulation} from "./Simulation";


(function Styles() {
    const stylesheet = document.createElement("style");
    stylesheet.innerHTML = `
        .options-panel {
            position: absolute;
            right: 10px;
            top: 10px;
        }

        .options-panel-header {
            height: 20px;
            background-color: gray;

            border-top-right-radius: 15px;
            border-top-left-radius: 15px;

            padding-left: 10px;
            padding-top: 3px;
            font-size: 15px;
            color: pink;
        }
        .options-panel-header:hover {
            cursor: move;
        }

        .options-panel-content {
            padding: 10px;
            text-align: center;
            color: black;

            border: solid 1px black;
            border-radius: 15px;
            border-top-right-radius: 0px;
            border-top-left-radius: 0px;
        }
        .options-panel-content > div {
            margin-bottom: 10px;
        }
        .options-panel-content > div:last-child {
            margin-bottom: 0px;
        }
        .options-panel-content label {
            display: block;
            font-weight: 600;
            margin-bottom: 5px;
        }
        .options-panel-content input {
            width: 35px;
            margin-left: 2px;
            border: solid 1px gray;
            border-radius: 5px;
            text-align: left;
        }
    `;
    // stylesheet.type = "text/css";

    document.head.appendChild(stylesheet);
})();



type BaseOption = {
    label: string;
}
type NumberOption = BaseOption & {
    type: "integer" | "float";
    min: number;
    max: number;
    step?: number;
}
type ArrayOption = BaseOption & {
    type: "array";
    elements: Omit<NumberOption, "label">;
}
type Option = NumberOption | ArrayOption;

type Options<T> = { [K in keyof T]: Option };

function html<K extends keyof HTMLElementTagNameMap>(type: K, props?: Partial<{ [L in keyof HTMLElementTagNameMap[K]]: HTMLElementTagNameMap[K][L] }>, ...children: (HTMLElement | string)[]): HTMLElementTagNameMap[K] {
    const el = document.createElement<K>(type);
    Object.entries(props ?? {}).forEach(([key, val]) => {
        el[key] = val;
    });
    children.forEach((child) => {
        if (typeof child === "string")
            el.innerHTML += child;
        else
            el.appendChild(child);
    });
    return el;
}


export class OptionsPanel<T extends Record<string, any>> {
    private sim: Simulation<T>;
    private options: Options<Partial<T>>;

    private optionsPanel: HTMLDivElement;
    private optionsPanelHeader: HTMLDivElement;
    private optionsPanelContent: HTMLDivElement;

    public constructor(sim: Simulation<T>, options: Options<Partial<T>>) {
        this.sim = sim;
        this.options = options;

        this.optionsPanel = html("div", { className: "options-panel" },
            (this.optionsPanelHeader = html("div", { className: "options-panel-header" }, "Options")),
            (this.optionsPanelContent = html("div", { className: "options-panel-content" }))
        );
        document.body.appendChild(this.optionsPanel);

        // Setup panel dragging
        (() => {
            let pos0 = V();
            let pos = V();

            // Attach listener for beginning of drag
            this.optionsPanelHeader.onmousedown = (ev) => {
                ev.preventDefault();

                pos0 = V(ev.clientX, ev.clientY);

                // Attach on drag listener
                const onDrag = (ev: MouseEvent) => {
                    ev.preventDefault();
                    pos = pos0.sub(ev.clientX, ev.clientY);
                    pos0 = V(ev.clientX, ev.clientY);

                    this.optionsPanel.style.left = `${this.optionsPanel.offsetLeft - pos.x}px`;
                    this.optionsPanel.style.top = `${this.optionsPanel.offsetTop - pos.y}px`;
                    this.optionsPanel.style.right = "unset";
                }
                document.addEventListener("mousemove", onDrag);

                // Attach on mouse up listener
                const onMouseUp = () => {
                    document.removeEventListener("mouseup", onMouseUp);
                    document.removeEventListener("mousemove", onDrag);
                }
                document.addEventListener("mouseup", onMouseUp);
            }

        })();

        this.update();
    }

    public update(): void {
        const reupdate = () => this.update();
        const sim = this.sim;
        const data = sim.getSim();

        this.optionsPanelContent.innerHTML = "";

        Object.entries(this.options).forEach(([key, option]) => {
            console.log("asdd");
            function getHTML(): HTMLElement {
                if (option.type === "integer" || option.type === "float") {
                    const val = data[key] as number;
                    return html("input", { id: `sim-${key}`, type: "number", value: `${val}`,
                                min: `${option.min}`, max: `${option.max}`, step: `${option.step}`,
                                onchange: (ev) => { sim.onSimChange({ [key]: (ev.target as HTMLInputElement).valueAsNumber } as Partial<T>); console.log("ASDDSAASD"); reupdate(); } }
                        )
                } else if (option.type === "array") {
                    const vals = data[key] as number[];
                    return html("div", { id: `sim-${key}` },
                        ...vals.map((val, i) =>
                            html("input", { type: "number", value: `${val}`,
                                            min: `${option.elements.min}`, max: `${option.elements.max}`, step: `${option.elements.step}`,
                                            onchange: (ev) => { sim.onSimChange({ [key]: [
                                                ...vals.slice(0, i),
                                                (ev.target as HTMLInputElement).valueAsNumber,
                                                ...vals.slice(i+1)
                                            ] } as Partial<T>); reupdate(); } }
                            ))
                        )
                }

                throw new Error(`Unknown option type: ${option.type}!`);
            }

            this.optionsPanelContent.appendChild(
                html("div", { },
                    html("label", { htmlFor: `sim-${key}` }, option.label),
                    getHTML()
                )
            );
        });
    }
}