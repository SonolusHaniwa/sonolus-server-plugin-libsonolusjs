import { build } from 'sonolus.js'
import { engineConfiguration } from './engine/configuration'
import { engineData } from './engine/data'

export const buildOutput = build({
    engine: {
        configuration: engineConfiguration,
        data: engineData,
    },

    level: {
        data: {
            bgmOffset: 0,
            entities: []
        },
    },
})