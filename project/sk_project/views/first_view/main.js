var application = require('application')


module.exports = class SK_View extends SK_RootView {
    constructor(opt){
        super(opt)
        
        this.info = {
            title: 'SK iPlug2 Demo',

            width: 1000,
            height: 512,
            minimizable: true,
            maximizable: true,

            minWidth: 500,
            minHeight: 580,

            maxWidth: 1500,
            maxHeight: 1580,

            //alwaysOnTop: true,
            //skipTaskbar: true,

            noTitle: true,

            show: true,

            //mainWindow: true

            //frame: false,
            transparent: true,

            backgroundColor: 'rgba(200, 124, 85, 0.5)'
        }
    }

    onForwardUserData(auth_token) {
        return new Promise(async resolve => {
            
            resolve({
                name: application.name
            })
        })
    }
}