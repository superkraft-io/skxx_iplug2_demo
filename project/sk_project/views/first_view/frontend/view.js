

class SK_App_View extends sk_ui_component {
    constructor(opt){
        super(opt)


        


        var web = require('web')

        this.add.label(_c => {
            _c.text = 'Welcome to Superkraft :)'
            _c.marginBottom = 64
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