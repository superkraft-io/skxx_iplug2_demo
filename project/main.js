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

        var { BrowserWindow } = require('proton')

        var wnd = new BrowserWindow({
             //movable: false,
            //resizable: true,
            //maxWidth: 500,
            //maxHeight: 300,
            //minWidth: 300,
            //minHeight: 200,
            //center: true,
            //alwaysOnTop: true,
        })

        setInterval(() => {
            //var resizableVal = wnd.resizable
            //wnd.resizable = !resizableVal

            //wnd.center()

            //var val = wnd.isAlwaysOnTop()
            //wnd.setAlwaysOnTop(!val)

            var attribute = 'movable'
            var val = wnd[attribute]
            wnd[attribute] = !val
        }, 1000)
    }

    postSKInit(sk) {
        console.log('Post-SK initalization')
    }
}
