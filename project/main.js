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
            //fullscreen: true
            frame: false,
            thickFrame: false
        })


        var arrIdx = -1
        var colors = ['darkcyan', '#60a23d', 'rgb(171 0 61)', 'hsl(271.35deg 100% 47.92%)']
        setInterval(() => {
            //var resizableVal = wnd.resizable
            //wnd.resizable = !resizableVal

            //wnd.center()

            //var val = wnd.isAlwaysOnTop()
            //wnd.setAlwaysOnTop(!val)

            
            var attribute = 'thickFrame'
            var val = wnd[attribute]
            wnd[attribute] = !val
            wnd.title = attribute + ' = ' + !val
            

            /*arrIdx++
            if (arrIdx >= colors.length) arrIdx = 0
            wnd.backgroundColor = colors[arrIdx]
            wnd.title = colors[arrIdx]*/
        }, 3000)
    }

    postSKInit(sk) {
        console.log('Post-SK initalization')
    }
}
