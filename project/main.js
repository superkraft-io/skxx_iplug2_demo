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
            //transparent: true,
            //backgroundColor: 'rgba(255,0,0,0.5)',
            //frame: false,
            //roundness: 25,


            //movable: false,
            //resizable: true,
            //maximizable: true,
                //fullscreenable: false,
            //minimizable: false,
            //closable: false,

            /*maxWidth: 500,
            maxHeight: 300,
            minWidth: 300,
            minHeight: 200*/
            
            //thickFrame: false

            //skipTaskbar: true,
            //focusable: false

            //show: false,

            //x: 100,
            //y: 300,
            //center: false,
            //alwaysOnTop: true,
            fullscreen: true
        })


        /*
        var opacity = 1
        setInterval(() => {
            opacity -= 0.02
            if (opacity < 0) opacity = 1
            wnd.setOpacity(opacity)
        }, 10)
        */
        
        var arrIdx = -1
        var colors = ['darkcyan', '#60a23d', 'rgb(171 0 61)', 'hsl(271.35deg 100% 47.92%)']
        var sizes = [{w: 32, h: 64}, {w: 132, h: 297}, {w: 400, h: 58}]

        setInterval(() => {
            //var resizableVal = wnd.resizable
            //wnd.resizable = !resizableVal

            //wnd.center()

            //var val = wnd.isAlwaysOnTop()
            //wnd.setAlwaysOnTop(!val)

            
            /*var attribute = 'fullscreen'
            var val = wnd[attribute]
            wnd[attribute] = !val
            wnd.title = attribute + ' = ' + !val
            */
            
            
            
            

            /*arrIdx++
            if (arrIdx >= colors.length) arrIdx = 0
            wnd.backgroundColor = colors[arrIdx]
            wnd.title = colors[arrIdx]*/

            /*arrIdx++
            if (arrIdx >= sizes.length) arrIdx = 0
            var size = sizes[arrIdx]
            wnd.width = size.w
            wnd.height = size.h*/
        }, 3000)
    }

    postSKInit(sk) {
        console.log('Post-SK initalization')
    }
}
