var fs = require('fs')

var skApp = {}

module.exports = class SK_App_Main {
    constructor() {

    }

    preSKInit(skOpts) {
        console.log('Pre-SK initialization...')

        skOpts.config = '/config.json'
        skApp.config = JSON.parse(fs.readFileSync(skOpts.config))
    }

    preSKStart() {
        console.log('Pre-SK start...')

        //Initialize all your modules here
    }

    postSKInit(sk) {
        console.log('Post-SK initalization')
    }
}
