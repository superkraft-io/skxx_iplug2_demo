class sk_ui_tab_parameters extends sk_ui_component {
    constructor(opt){
        super(opt)

        this.styling = ' top left ttb fullwidth fullheight'

        this.add.text(_c => {
            _c.styling += ' fullwidth'
            _c.wrap = true
            _c.text = 'Below is a set of parameters that are available in the plugin.'
        })

        this.add.text(_c => {
            _c.styling += ' fullwidth'
            _c.wrap = true
            _c.text = 'The parameters can be automatable in your DAW and Superkraft will handle all the logic for reading and writing the parameter values.'
        })


        this.add.group(_c => {
            _c._header.weight = 'bold'
            _c._header.size = 18
            _c.header = 'Boolean (0 and 1)'

            _c.container.setup(_c => {
                _c.add.switch(_c => {
                    _c.pluginParamID = 'Boolean'
                    _c.text = 'Boolean'
                })
            })

        })


        this.add.group(_c => {
            _c._header.weight = 'bold'
            _c._header.size = 18
            _c.header = 'Integer (1 to 9, stepping 1)'

            _c.container.setup(_c => {
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
            _c.header = 'Double (0 to 100, no stepping, smooth)'

            _c.container.setup(_c => {
                _c.add.slider(_c => {
                    _c.pluginParamID = 'Double'

                    _c.style.maxWidth = '300px'

                    _c.min = 0
                    _c.max = 100
                    _c.defaultValue = 50

                    _c.smooth = true
                })
            })

        })


        this.add.group(_c => {
            _c._header.weight = 'bold'
            _c._header.size = 18
            _c.header = 'List'

            _c.container.setup(_c => {
                _c.add.list(_c => {
                    _c.pluginParamID = 'List'

                    _c.highlightOnSelect = true

                    _c.style.border = 'solid 1px var(--sk_ui_color_dark_grey_2)'
                    _c.roundness = 12
                    _c.backgroundColor = 'var(--sk_ui_color_very_dark_grey_2)'

                    _c.items.add({
                        label: 'Option 1'
                    })

                    _c.items.add({
                        label: 'Option 2'
                    })

                    _c.items.add({
                        label: 'Option 3'
                    })


                    _c.onItemSelected = async item => {
                        var paramIdx = item.idx
                        var paramID = item.info.label

                        _c.dawPluginParamInfo.busyWriting = true
                        _c.dawPluginParamInfo.busyChanging = true
                        
                        await _c.dawPluginParamInfo.writeValue({value: paramIdx})

                        _c.dawPluginParamInfo.busyWriting = false
                        _c.dawPluginParamInfo.busyChanging = false
                        
                    }
                })
            })

        })
    }
}