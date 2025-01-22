var application = require('application')


module.exports = class SK_View extends SK_RootView {
    constructor(opt){
        super(opt)
        
        this.info = {
            title: 'SK JUCE',

            width: 1000,
            height: 512,
            minimizable: true,
            maximizable: true,

            //minWidth: 1500,
            minHeight: 580,

            //alwaysOnTop: true,
            //skipTaskbar: true,

            noTitle: true,

            show: true,

            mainWindow: true
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