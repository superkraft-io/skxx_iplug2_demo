class SK_App_View extends sk_ui_component {
    constructor(opt){
        super(opt)
        

        this.add.label(_c => {
            _c.text = 'Welcome to Superkraft :)'
        })

        this.add.button(_c => {
            _c.text = 'Click me!'

            _c.onClick = () => {
                alert('Clicked!')
            }
        })
    }
}