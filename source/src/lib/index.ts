import { EngineInfo, LevelData } from 'sonolus-core'
import { Resource } from './Resource'

const archetypes = require('./archetypes')

export const version = ''

export const engineInfo = {
    name: 'hwpl',
    version: 7,
    title: {
        en: ''
    },
    subtitle: {
        en: ''
    },
    author: {
        en: '',
    },
    description: {
        en: [

        ].join('\n'),
    },
} as const satisfies Partial<EngineInfo>

export const engineConfiguration = new Resource('EngineConfiguration')
export const engineData = new Resource('EngineData')
export const engineThumbnail = new Resource('thumbnail.png')