import {Simulation} from "utils/Simulation";
import {OptionsPanel} from "utils/OptionsPanel";

import "utils/Array";



const initialSim = {
    N: 2,
    m: [1, 0.5],
    L: [3.5, 3],
    theta: [1.6, 2],
    dTheta: [0, 0],

    _pointers: [0,0,0,0] as [number, number, number, number]
};

const sim = new Simulation<typeof initialSim>("canvas",
    (Sim = initialSim, change) => {
        if (change?.N) {
            const N = change.N;
            const nextSim = {
                N,
                m:      Array(N).fill(0).map((_, i) => (i < Sim.N ? Sim.m[i]      : ((1 - i/N)))),
                L:      Array(N).fill(0).map((_, i) => (i < Sim.N ? Sim.L[i]      : ((1 - i/N) + 2.5))),
                theta:  Array(N).fill(0).map((_, i) => (i < Sim.N ? Sim.theta[i]  : Sim.theta[Sim.N-1])),
                dTheta: Array(N).fill(0).map((_, i) => (i < Sim.N ? Sim.dTheta[i] : 0)),

                _pointers: [0,0,0,0] as [number, number, number, number]
            };

            return nextSim;
        }
        return Sim;
    },
    (s) => {
        // sim update
    },
    (p, s) => {
        // sim render
    }
);


const panel = new OptionsPanel(sim, {
    N:      { label: "# of bobs",          type: "integer", min: 1, max: 20, step: 1, inputType: "slider" },
    m:      { label: "Mass of bobs",       type: "array", elements: { type: "float", min: 0.01, max: 20  } },
    L:      { label: "Length of strings",  type: "array", elements: { type: "float", min: 0.01, max: 20  } },
    theta:  { label: "Angles",             type: "array", elements: { type: "float", min: 0,    max: 360 } },
    dTheta: { label: "Angular Velocities", type: "array", elements: { type: "float", min: -20,  max: 20  } }
});

