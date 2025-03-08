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

        return
        
        //Initialize all your modules here

        var { app, BrowserWindow } = require('proton')

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
            //fullscreen: true
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

            
            /*var attribute = 'alwaysOnTop'
            var val = wnd[attribute]
            wnd[attribute] = !val
            wnd.title = attribute + ' = ' + !val*/
            
            
            
            
            

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


        var wndEvents = [
            //{id: 'close'        , log: true},         //macos
            //{id: 'closed'       , log: true},         //macos
            //{id: 'blur'         , log: false},        //macos
            //{id: 'focus'        , log: false},        //macos
            //{id: 'show'         , log: false},        //macos
            //{id: 'hide'         , log: false},        //macos
            //{id: 'maximize'     , log: false},        //macos
            //{id: 'unmaximize'   , log: false},        //macos
            //{id: 'minimize'     , log: false},        //macos
            //{id: 'restore'      , log: false},        //macos
            //{id: 'will-resize'  , log: true},         //macos
            //{id: 'resize'       , log: true},         //macos
            //{id: 'resized'      , log: true},         //macos
            //{id: 'will-move'    , log: true},         //macos
            //{id: 'move'         , log: true},         //macos
            //{id: 'moved'        , log: true},         //macos
            //{id: 'enter-full-screen', log: true},     //macos
            //{id: 'leave-full-screen', log: true},     //macos
            //{id: 'swipe'            , log: true},     //macos
            //{id: 'rotate-gesture'   , log: true},     //macos
            //{id: 'sheet-begin'      , log: true},
            //{id: 'sheet-end'        , log: true},

            {id: 'ready-to-show'        , log: true},

            {id: 'always-on-top-changed', log: false},   //doesn't seem to do anything on ElectronJS, so I'll ignore this

            {id: 'new-window-for-tab'   , log: false},  // what does this one even do?
            {id: 'app-command'          , log: false},  // windows only !!!
            {id: 'system-context-menu'  , log: false},  // windows only !!!
            {id: 'session-end'          , log: false},  // windows only !!!
        ]
    
    
        var listenToWndEvent = opt => {
            wnd.on(opt.id, (arg1, arg2, arg3, arg4)=>{
                var x = 0
    
                if (opt.id === 'close'){
                    arg1.returnValue = false
                }

                if (!opt.log) return
                
                console.log('-----------------------')
    
                console.log(opt.id)
                console.log('')
                
                if (arg1){
                    if (Object.keys(arg1).length > 0){
                        console.log('arg1')
                        console.log(JSON.stringify(arg1))
                        console.log('')
                    }
                }
    
                if (arg2){
                    console.log('arg2')
                    console.log(arg2)
                    console.log('')
                }
                
                if (arg3){
                    console.log('arg3')
                    console.log(arg3)
                    console.log('')
                }
    
                if (arg4){
                    console.log('arg4')
                    console.log(arg4)
                    console.log('')
                }
            })
        }
    
        for (var i in wndEvents) listenToWndEvent(wndEvents[i])
       

        app.on('ready', ()=>{
            console.log('app is ready (on ready event)')
        })
        
        app.whenReady().then(()=>{
            console.log('app is ready (whenReady promise)')

            console.log('loading URL test.html')

            wnd.loadURL('/sk:project/test.html')
        })
    }

    postSKInit(sk) {
        console.log('Post-SK initalization')
    }
}
