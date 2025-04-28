

class SK_App_View extends sk_ui_component {
    constructor(opt){
        super(opt)

        sk.app.body.styling = 'center tbb scrollable'

        this.styling = 'left middle ttb scrollable'
        
        var web = require('web')

        this.add.label(_c => {
            _c.text = 'Welcome to Superkraft for iPlug2 😎'
            _c.marginBottom = 64
        })

        
         this.add.component(_c => {
            _c.styling = 'top left fullwidth fullheight'
            _c.vertical = false
            
            this.sectionsList = _c.add.tab_btns()
            this.sectionsList.selectItem({key: 'id', value: 'parameters'})
        })
    }
}