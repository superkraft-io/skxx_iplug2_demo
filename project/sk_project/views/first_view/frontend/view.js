

class SK_App_View extends sk_ui_component {
    constructor(opt){
        super(opt)

        this.styling = 'left middle ttb scrollable'
        
        var web = require('web')

        this.add.label(_c => {
            _c.text = 'Welcome to Superkraft for iPlug2 😎'
            _c.marginBottom = 64
        })

        this.add.group(_c => {
            _c._header.weight = 'bold'
            _c._header.size = 18
            _c.header = 'DAW Plugin Parameters'
            _c.width = 300

            _c.container.setup(_c => {
                _c.add.text(_c => {
                    _c.styling += ' fullwidth'
                    _c.wrap = true
                    _c.text = 'Below is a set of parameters that are available in the plugin.'
                })

                _c.add.text(_c => {
                    _c.styling += ' fullwidth'
                    _c.wrap = true
                    _c.text = 'The parameters can be automatable in your DAW and Superkraft will handle all the logic for reading and writing the parameter values.'
                })

                _c.add.switch(_c => {
                    _c.pluginParamID = 'Boolean'
                    _c.text = 'Boolean'
                })

                _c.add.slider(_c => {
                    _c.pluginParamID = 'Integer'

                    _c.style.maxWidth = '300px'

                    _c.step = 1
                    _c.min = 1
                    _c.max = 9
                    _c.defaultValue = 5

                    _c.smooth = false
                })
            })

        })

        this.add.group(_c => {
            _c._header.weight = 'bold'
            _c._header.size = 18
            _c.header = 'Native Action'

            _c.container.add.roundedBtn(_c => {
                _c.icon = 'code'
                _c.text = 'Test'

                _c.onClick = async () => {
                    var res = await sk.nativeActions.test({ key: 'value' })
                    alert('response from hard backend (c++):\n\n' + JSON.stringify(res))
                }
            })

        })


        this.add.group(_c => {
            _c._header.weight = 'bold'
            _c._header.size = 18
            _c.header = 'Web Requests'

            _c.container.add.text(_c => {
                _c.wrap = true
                _c.width = 380
                _c.text = 'Use sk:web.get(), .post(), and download() to conduct HTTP operations.\n\nThe sk:web module ensures threaded HTTP requests that do not block the UI and uses CURL.'
            })

            _c.container.add.component(_c => {
                _c.styling += ' fullwidth'
                _c.vertical = false
                _c.add.roundedBtn(_c => {
                    _c.styling += ' fullwidth'
                    _c.icon = 'globe'
                    _c.text = 'GET'

                    _c.onClick = async () => {
                        var res = await web.post({ url: 'https://httpbin.org/post', key: 'value' })
                        alert('response from https://httpbin.org/post:\n\n' + JSON.stringify(res))
                    }
                })

                _c.add.roundedBtn(_c => {
                    _c.styling += ' fullwidth'
                    _c.icon = 'globe'
                    _c.text = 'POST'

                    _c.onClick = async () => {
                        var res = await web.post({ url: 'https://httpbin.org/post', key: 'value' })
                        alert('response from https://httpbin.org/post:\n\n' + JSON.stringify(res))
                    }
                })
            })

            _c.container.add.component(_c => {
                _c.styling += ' fullwidth'
                _c.vertical = false
                _c.add.roundedBtn(_c => {
                    _c.icon = 'globe'
                    _c.text = 'DOWNLOAD'
                    _c.width = 220

                    _c.onClick = async () => {
                        var res = await web.post({ url: 'https://httpbin.org/post', key: 'value' })
                        alert('response from https://httpbin.org/post:\n\n' + JSON.stringify(res))
                    }
                })

                _c.add.progressBar(_c => {
                    _c.styling += ' fullwidth'
                    _c.height = 8
                    _c.as.line({

                    })
                })
            })

        })
        
    }
}