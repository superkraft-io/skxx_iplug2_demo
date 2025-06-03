#pragma once

#if defined(SK_BUNDLER_MODE_DEEP)
    #include "./deep/groups/sk_soft_backend_bundle_group_0.h"
#elif defined(SK_BUNDLER_MODE_SHALLOW)
    #include "./shallow/groups/sk_soft_backend_bundle_group_0.h"
#endif

BEGIN_SK_NAMESPACE


class SK_SoftBackend_Bundle_Entry_Info {
public:
    size_t idx = -1;
    size_t offset = -1;
    size_t size = -1;
    int groupIdx = -1;

    bool isFolder = false;
    SK_String filename;

    SK_String folderEntries;
    SK_String fileEntries;

    SK_SoftBackend_Bundle_Data_Group_Root* group;
    
    SK_SoftBackend_Bundle_Entry_Info(
        const size_t _offset,
        const size_t _size,
        const int _groupIdx,
        const size_t _idx,
        void* _group,
        bool _isFolder = false,
        const SK_String& _filename = "",
        const SK_String& _folderEntries = "",
        const SK_String& _fileEntries = ""
    ) : offset(_offset),    // Initialization list
        size(_size),
        groupIdx(_groupIdx),
        idx(_idx),
        group(static_cast<SK_SoftBackend_Bundle_Data_Group_Root*>(_group)),
        isFolder(_isFolder),
        filename(_filename),
        folderEntries(_folderEntries),
        fileEntries(_fileEntries)
    {
        // Constructor body (empty in this case)
    }
    
    SK_String dataAs_SKString() {
        void* _offsets;    // Will hold `offsets` array address
        void* _sizes;      // Will hold `sizes` array address
        void* _data;       // Will hold `data` array address
        size_t _data_size; // Will hold `data_size`

        // Pass addresses of the pointers (&_offsets, &_sizes, &_data)
        group->getPointers(&_offsets, &_sizes, &_data, &_data_size);

        size_t end = offset + size;
        if (end > _data_size) {
            throw std::runtime_error("Corrupted data: size exceeds buffer");
        }

        // Create string directly from the source range (zero-copy if possible)
        const char* data_start = static_cast<const char*>(_data) + offset;
        return SK_String(std::string(data_start, size));  // Efficient construction
    }
    
    nlohmann::json readDir(){
        nlohmann::json list = nlohmann::json::array();
        
        
        if (folderEntries.length() > 0 && fileEntries.length() > 0 ){
            
            if (folderEntries.length() > 0){
                //add folders
                std::vector<std::string> folders = folderEntries.split(",");
                unsigned int folderEntries_size = folders.size();
                if (size > 0) {
                    for (unsigned int i = 0; i < folderEntries_size; i++) {
                        std::string entryName = folders[i];
                        list.push_back(nlohmann::json{
                            {"type", "dir"},
                            {"name", entryName}
                        });
                    }
                }
            }
            
            if (fileEntries.length() > 0){
                //add folders
                std::vector<std::string> files = fileEntries.split(",");
                unsigned int fileEntries_size = files.size();
                if (size > 0) {
                    for (unsigned int i = 0; i < fileEntries_size; i++) {
                        std::string entryName = files[i];
                        list.push_back(nlohmann::json{
                            {"type", "dir"},
                            {"name", entryName}
                        });
                    }
                }
            }
            
            
            
            std::sort(list.begin(), list.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
                return a["name"] < b["name"];
            });
        }
        
        return list;
    }
};

class SK_SoftBackend_Bundle_Library {
public:
    std::vector<void*> groups = {
        new SK_SoftBackend_Bundle_Data_Group_0()

    };

    std::map<std::string, SK_SoftBackend_Bundle_Entry_Info*> fileEntries {
       {"/config.json", new SK_SoftBackend_Bundle_Entry_Info(0, 96, 0, 0, groups[0], false, "config.json", "", "")},
       {"/main.js", new SK_SoftBackend_Bundle_Entry_Info(96, 6464, 0, 1, groups[0], false, "main.js", "", "")}

    };

    std::map<std::string, SK_SoftBackend_Bundle_Entry_Info*> folderEntries {
       {"/", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_globalActions,sk_globalFrontend,sk_nativeActions,sk_posts,sk_project,sk_templates,superkraft,test", "config.json,main.js")},
       {"/sk_globalActions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "")},
       {"/sk_globalFrontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "")},
       {"/sk_nativeActions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "")},
       {"/sk_posts", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "")},
       {"/sk_project", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "views", "")},
       {"/sk_project/views", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "first_view", "")},
       {"/sk_project/views/first_view", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "actions,frontend", "head.ejs,main.js")},
       {"/sk_project/views/first_view/actions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "testAction.js")},
       {"/sk_project/views/first_view/frontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui", "view.css,view.js")},
       {"/sk_project/views/first_view/frontend/sk_ui", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui_tab_btns,sk_ui_tab_nativeActions,sk_ui_tab_parameters,sk_ui_tab_web", "")},
       {"/sk_project/views/first_view/frontend/sk_ui/sk_ui_tab_btns", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_tab_btns.css,sk_ui_tab_btns.js")},
       {"/sk_project/views/first_view/frontend/sk_ui/sk_ui_tab_nativeActions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_tab_nativeActions.css,sk_ui_tab_nativeActions.js")},
       {"/sk_project/views/first_view/frontend/sk_ui/sk_ui_tab_parameters", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_tab_parameters.css,sk_ui_tab_parameters.js")},
       {"/sk_project/views/first_view/frontend/sk_ui/sk_ui_tab_web", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_tab_web.css,sk_ui_tab_web.js")},
       {"/sk_templates", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "")},
       {"/superkraft", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "complexity,engines,frontend,modules,ui", "sk_emptyEJS.ejs,sk_rootEngine.js,sk_rootViewCore.js,sk_superkraft.js,template.ejs")},
       {"/superkraft/complexity", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "backend,frontend", "")},
       {"/superkraft/complexity/backend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "actions", "sk_complexity.js")},
       {"/superkraft/complexity/backend/actions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "bake.js,getComplexityInfo.js")},
       {"/superkraft/complexity/frontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "codeEditor,editor", "comm.js,complexity.css,complexity.js,icons.js,selectionManager.js")},
       {"/superkraft/complexity/frontend/codeEditor", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "codemirror", "bakery.js,codeEditor.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "addon,bin,demo,doc,keymap,lib,mode,src,test,theme", ".editorconfig,.npmignore,AUTHORS,LICENSE,index.html,package.json,rollup.config.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "comment,dialog,display,edit,fold,hint,lint,merge,mode,runmode,scroll,search,selection,tern,wrap", "")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/comment", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "comment.js,continuecomment.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/dialog", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dialog.css,dialog.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/display", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "autorefresh.js,fullscreen.css,fullscreen.js,panel.js,placeholder.js,rulers.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/edit", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "closebrackets.js,closetag.js,continuelist.js,matchbrackets.js,matchtags.js,trailingspace.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/fold", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "brace-fold.js,comment-fold.js,foldcode.js,foldgutter.css,foldgutter.js,indent-fold.js,markdown-fold.js,xml-fold.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/hint", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "anyword-hint.js,css-hint.js,html-hint.js,javascript-hint.js,show-hint.css,show-hint.js,sql-hint.js,xml-hint.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/lint", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "coffeescript-lint.js,css-lint.js,html-lint.js,javascript-lint.js,json-lint.js,lint.css,lint.js,yaml-lint.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/merge", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "merge.css,merge.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/mode", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "loadmode.js,multiplex.js,multiplex_test.js,overlay.js,simple.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/runmode", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "colorize.js,runmode-standalone.js,runmode.js,runmode.node.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/scroll", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "annotatescrollbar.js,scrollpastend.js,simplescrollbars.css,simplescrollbars.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/search", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "jump-to-line.js,match-highlighter.js,matchesonscrollbar.css,matchesonscrollbar.js,search.js,searchcursor.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/selection", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "active-line.js,mark-selection.js,selection-pointer.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/tern", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "tern.css,tern.js,worker.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/addon/wrap", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "hardwrap.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/bin", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "authors.sh,lint,release,source-highlight,upload-release.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/demo", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "activeline.html,anywordhint.html,bidi.html,btree.html,buffers.html,changemode.html,closebrackets.html,closetag.html,complete.html,emacs.html,folding.html,fullscreen.html,hardwrap.html,html5complete.html,indentwrap.html,lint.html,loadmode.html,marker.html,markselection.html,matchhighlighter.html,matchtags.html,merge.html,multiplex.html,mustache.html,panel.html,placeholder.html,preview.html,requirejs.html,resize.html,rulers.html,runmode-standalone.html,runmode.html,search.html,simplemode.html,simplescrollbars.html,spanaffectswrapping_shim.html,sublime.html,tern.html,theme.html,trailingspace.html,variableheight.html,vim.html,visibletabs.html,widget.html,xmlcomplete.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/doc", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "logos", "activebookmark.js,docs.css,internals.html,logo.png,logo.svg,manual.html,realworld.html,releases.html,reporting.html,source_sans.woff,upgrade_v2.2.html,upgrade_v3.html,upgrade_v4.html,yinyang.png")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/doc/logos", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "4me.svg,anvil.png,artcompiler.svg,cargo.svg,codepen.svg,desmos.svg,executeprogram.svg,holmusk.svg,jetbrains.svg,observable.svg,primo.svg,prisma.svg")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/keymap", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "emacs.js,sublime.js,vim.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/lib", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "codemirror.css,codemirror.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "apl,asciiarmor,asn.1,asterisk,brainfuck,clike,clojure,cmake,cobol,coffeescript,commonlisp,crystal,css,cypher,d,dart,diff,django,dockerfile,dtd,dylan,ebnf,ecl,eiffel,elm,erlang,factor,fcl,forth,fortran,gas,gfm,gherkin,go,groovy,haml,handlebars,haskell,haskell-literate,haxe,htmlembedded,htmlmixed,http,idl,javascript,jinja2,jsx,julia,livescript,lua,markdown,mathematica,mbox,mirc,mllike,modelica,mscgen,mumps,nginx,nsis,ntriples,octave,oz,pascal,pegjs,perl,php,pig,powershell,properties,protobuf,pug,puppet,python,q,r,rpm,rst,ruby,rust,sas,sass,scheme,shell,sieve,slim,smalltalk,smarty,solr,soy,sparql,spreadsheet,sql,stex,stylus,swift,tcl,textile,tiddlywiki,tiki,toml,tornado,troff,ttcn,ttcn-cfg,turtle,twig,vb,vbscript,velocity,verilog,vhdl,vue,wast,webidl,xml,xquery,yacas,yaml,yaml-frontmatter,z80", "index.html,meta.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/apl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "apl.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/asciiarmor", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "asciiarmor.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/asn.1", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "asn.1.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/asterisk", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "asterisk.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/brainfuck", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "brainfuck.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/clike", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "clike.js,index.html,scala.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/clojure", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "clojure.js,index.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/cmake", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "cmake.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/cobol", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "cobol.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/coffeescript", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "coffeescript.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/commonlisp", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "commonlisp.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/crystal", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "crystal.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/css", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "css.js,gss.html,gss_test.js,index.html,less.html,less_test.js,scss.html,scss_test.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/cypher", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "cypher.js,index.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/d", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "d.js,index.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/dart", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dart.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/diff", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "diff.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/django", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "django.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/dockerfile", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dockerfile.js,index.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/dtd", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dtd.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/dylan", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dylan.js,index.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/ebnf", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "ebnf.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/ecl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "ecl.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/eiffel", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "eiffel.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/elm", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "elm.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/erlang", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "erlang.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/factor", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "factor.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/fcl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "fcl.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/forth", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "forth.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/fortran", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "fortran.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/gas", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "gas.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/gfm", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "gfm.js,index.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/gherkin", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "gherkin.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/go", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "go.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/groovy", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "groovy.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/haml", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "haml.js,index.html,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/handlebars", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "handlebars.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/haskell", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "haskell.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/haskell-literate", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "haskell-literate.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/haxe", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "haxe.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/htmlembedded", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "htmlembedded.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/htmlmixed", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "htmlmixed.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/http", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "http.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/idl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "idl.js,index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/javascript", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,javascript.js,json-ld.html,test.js,typescript.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/jinja2", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,jinja2.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/jsx", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,jsx.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/julia", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,julia.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/livescript", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,livescript.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/lua", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,lua.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/markdown", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,markdown.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/mathematica", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,mathematica.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/mbox", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,mbox.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/mirc", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,mirc.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/mllike", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,mllike.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/modelica", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,modelica.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/mscgen", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,mscgen.js,mscgen_test.js,msgenny_test.js,xu_test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/mumps", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,mumps.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/nginx", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,nginx.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/nsis", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,nsis.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/ntriples", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,ntriples.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/octave", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,octave.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/oz", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,oz.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/pascal", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,pascal.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/pegjs", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,pegjs.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/perl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,perl.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/php", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,php.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/pig", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,pig.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/powershell", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,powershell.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/properties", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,properties.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/protobuf", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,protobuf.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/pug", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,pug.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/puppet", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,puppet.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/python", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,python.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/q", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,q.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/r", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,r.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/rpm", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "changes", "index.html,rpm.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/rpm/changes", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/rst", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,rst.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/ruby", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,ruby.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/rust", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,rust.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/sas", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,sas.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/sass", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,sass.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/scheme", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,scheme.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/shell", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,shell.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/sieve", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,sieve.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/slim", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,slim.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/smalltalk", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,smalltalk.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/smarty", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,smarty.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/solr", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,solr.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/soy", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,soy.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/sparql", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,sparql.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/spreadsheet", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,spreadsheet.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/sql", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,sql.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/stex", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,stex.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/stylus", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,stylus.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/swift", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,swift.js,test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/tcl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,tcl.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/textile", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,test.js,textile.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/tiddlywiki", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,tiddlywiki.css,tiddlywiki.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/tiki", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,tiki.css,tiki.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/toml", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,toml.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/tornado", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,tornado.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/troff", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,troff.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/ttcn", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,ttcn.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/ttcn-cfg", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,ttcn-cfg.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/turtle", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,turtle.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/twig", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,twig.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/vb", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,vb.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/vbscript", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,vbscript.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/velocity", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,velocity.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/verilog", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,test.js,verilog.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/vhdl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,vhdl.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/vue", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,vue.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/wast", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,test.js,wast.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/webidl", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,webidl.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/xml", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,test.js,xml.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/xquery", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,test.js,xquery.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/yacas", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,yacas.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/yaml", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,yaml.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/yaml-frontmatter", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,yaml-frontmatter.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/mode/z80", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "index.html,z80.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "addon,display,edit,input,line,measurement,model,util", "codemirror.js,modes.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/addon", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "runmode", "")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/addon/runmode", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "codemirror-standalone.js,codemirror.node.js,runmode-standalone.js,runmode.node.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/display", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "Display.js,focus.js,gutters.js,highlight_worker.js,line_numbers.js,mode_state.js,operations.js,scroll_events.js,scrollbars.js,scrolling.js,selection.js,update_display.js,update_line.js,update_lines.js,view_tracking.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/edit", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "CodeMirror.js,commands.js,deleteNearSelection.js,drop_events.js,fromTextArea.js,global_events.js,key_events.js,legacy.js,main.js,methods.js,mouse_events.js,options.js,utils.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/input", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "ContentEditableInput.js,TextareaInput.js,indent.js,input.js,keymap.js,keynames.js,movement.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/line", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "highlight.js,line_data.js,pos.js,saw_special_spans.js,spans.js,utils_line.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/measurement", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "position_measurement.js,widgets.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/model", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "Doc.js,change_measurement.js,changes.js,chunk.js,document_data.js,history.js,line_widget.js,mark_text.js,selection.js,selection_updates.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/src/util", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "StringStream.js,bidi.js,browser.js,dom.js,event.js,feature_detection.js,misc.js,operation_group.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/test", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "annotatescrollbar.js,comment_test.js,contenteditable_test.js,doc_test.js,driver.js,emacs_test.js,html-hint-test.js,index.html,lint.js,mode_test.css,mode_test.js,multi_test.js,run.js,scroll_test.js,search_test.js,sql-hint-test.js,sublime_test.js,test.js,vim_test.js")},
       {"/superkraft/complexity/frontend/codeEditor/codemirror/theme", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "3024-day.css,3024-night.css,abbott.css,abcdef.css,ambiance-mobile.css,ambiance.css,ayu-dark.css,ayu-mirage.css,base16-dark.css,base16-light.css,bespin.css,blackboard.css,cobalt.css,colorforth.css,darcula.css,dracula.css,duotone-dark.css,duotone-light.css,eclipse.css,elegant.css,erlang-dark.css,gruvbox-dark.css,hopscotch.css,icecoder.css,idea.css,isotope.css,juejin.css,lesser-dark.css,liquibyte.css,lucario.css,material-darker.css,material-ocean.css,material-palenight.css,material.css,mbo.css,mdn-like.css,midnight.css,monokai.css,moxer.css,neat.css,neo.css,night.css,nord.css,oceanic-next.css,panda-syntax.css,paraiso-dark.css,paraiso-light.css,pastel-on-dark.css,railscasts.css,rubyblue.css,seti.css,shadowfox.css,solarized.css,ssms.css,the-matrix.css,tomorrow-night-bright.css,tomorrow-night-eighties.css,ttcn.css,twilight.css,vibrant-ink.css,vscode-dark.css,xq-dark.css,xq-light.css,yeti.css,yonce.css,zenburn.css")},
       {"/superkraft/complexity/frontend/editor", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "components", "editor.js")},
       {"/superkraft/complexity/frontend/editor/components", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "attributeEditor.js,iconList.js,objectTree.js,stylingEditor.js")},
       {"/superkraft/engines", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "dapp,skxx,wapp", "")},
       {"/superkraft/engines/dapp", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "frontend,global_actions,modules", "engine.js,rootView.js")},
       {"/superkraft/engines/dapp/frontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "engine_body.ejs,engine_style.css")},
       {"/superkraft/engines/dapp/global_actions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dialog.js,getInfo.js,get_UMS_BE_events.js,openURL.js,relaunch.js,setOnlineStatus.js,terminate.js,windowAction.js")},
       {"/superkraft/engines/dapp/modules", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_dapp_cursor", "sk_dapp_deeplink.js,sk_dapp_instanceMgr.js")},
       {"/superkraft/engines/dapp/modules/sk_dapp_cursor", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "frontend", "main.js")},
       {"/superkraft/engines/dapp/modules/sk_dapp_cursor/frontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui", "view.css,view.js")},
       {"/superkraft/engines/dapp/modules/sk_dapp_cursor/frontend/sk_ui", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui_dapp_cursor", "")},
       {"/superkraft/engines/dapp/modules/sk_dapp_cursor/frontend/sk_ui/sk_ui_dapp_cursor", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_dapp_cursor.css,sk_ui_dapp_cursor.js")},
       {"/superkraft/engines/skxx", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "frontend,global_actions,modules", "engine.js,rootView.js,rootView_bkp.js")},
       {"/superkraft/engines/skxx/frontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui", "engine_body.ejs,engine_style.css")},
       {"/superkraft/engines/skxx/frontend/sk_ui", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui_inputLabel,sk_ui_knobComponent,sk_ui_led,sk_ui_section,sk_ui_vu_meter", "")},
       {"/superkraft/engines/skxx/frontend/sk_ui/sk_ui_inputLabel", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_inputLabel.css,sk_ui_inputLabel.js")},
       {"/superkraft/engines/skxx/frontend/sk_ui/sk_ui_knobComponent", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui_knob", "sk_ui_knobComponent.css,sk_ui_knobComponent.js")},
       {"/superkraft/engines/skxx/frontend/sk_ui/sk_ui_knobComponent/sk_ui_knob", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_knob.css,sk_ui_knob.js")},
       {"/superkraft/engines/skxx/frontend/sk_ui/sk_ui_led", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_led.css,sk_ui_led.js")},
       {"/superkraft/engines/skxx/frontend/sk_ui/sk_ui_section", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_section.css,sk_ui_section.js")},
       {"/superkraft/engines/skxx/frontend/sk_ui/sk_ui_vu_meter", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_vu_meter.css,sk_ui_vu_meter.js")},
       {"/superkraft/engines/skxx/global_actions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dialog.js,getInfo.js,get_UMS_BE_events.js,openURL.js,relaunch.js,setOnlineStatus.js,terminate.js,windowAction.js")},
       {"/superkraft/engines/skxx/modules", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "ejs_skxx,skxx_electron", "")},
       {"/superkraft/engines/skxx/modules/ejs_skxx", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "ejs.js,ejs_skxx.js,ejs_template.js,ejs_utils.js")},
       {"/superkraft/engines/skxx/modules/skxx_electron", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "skxx_electron_app.js,skxx_electron_window.js")},
       {"/superkraft/engines/wapp", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "global_actions,modules", "engine.js,rootView.js")},
       {"/superkraft/engines/wapp/global_actions", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "getInfo.js")},
       {"/superkraft/engines/wapp/modules", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_wapp_mobile.js")},
       {"/superkraft/frontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "libs", "")},
       {"/superkraft/frontend/libs", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "fonts,formantic-ui,helpers,jquery,js-cookie,jsom,progressbarjs,sk_childMngr,sk_comm,sk_commands,sk_cursor,sk_dialog,sk_fileDrop,sk_hint,sk_l10n,sk_mobile,sk_shortcuts,sk_titlebar,sk_ums,sk_viewController,ua_parser", "fastclick.js,sk_helpers.js,sk_repeater.js,sk_thread.js,sk_tween.js,sortable.min.js")},
       {"/superkraft/frontend/libs/fonts", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "quicksand", "")},
       {"/superkraft/frontend/libs/fonts/quicksand", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "bold.ttf,light.ttf,medium.ttf,regular.ttf,semibold.ttf")},
       {"/superkraft/frontend/libs/formantic-ui", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "components,themes", "semantic.css,semantic.js,semantic.min.css,semantic.min.js")},
       {"/superkraft/frontend/libs/formantic-ui/components", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "accordion.css,accordion.js,accordion.min.css,accordion.min.js,ad.css,ad.min.css,api.js,api.min.js,breadcrumb.css,breadcrumb.min.css,button.css,button.min.css,calendar.css,calendar.js,calendar.min.css,calendar.min.js,card.css,card.min.css,checkbox.css,checkbox.js,checkbox.min.css,checkbox.min.js,comment.css,comment.min.css,container.css,container.min.css,dimmer.css,dimmer.js,dimmer.min.css,dimmer.min.js,divider.css,divider.min.css,dropdown.css,dropdown.js,dropdown.min.css,dropdown.min.js,embed.css,embed.js,embed.min.css,embed.min.js,emoji.css,emoji.min.css,feed.css,feed.min.css,flag.css,flag.min.css,flyout.css,flyout.js,flyout.min.css,flyout.min.js,form.css,form.js,form.min.css,form.min.js,grid.css,grid.min.css,header.css,header.min.css,icon.css,icon.min.css,image.css,image.min.css,input.css,input.min.css,item.css,item.min.css,label.css,label.min.css,list.css,list.min.css,loader.css,loader.min.css,menu.css,menu.min.css,message.css,message.min.css,modal.css,modal.js,modal.min.css,modal.min.js,nag.css,nag.js,nag.min.css,nag.min.js,placeholder.css,placeholder.min.css,popup.css,popup.js,popup.min.css,popup.min.js,progress.css,progress.js,progress.min.css,progress.min.js,rail.css,rail.min.css,rating.css,rating.js,rating.min.css,rating.min.js,reset.css,reset.min.css,reveal.css,reveal.min.css,search.css,search.js,search.min.css,search.min.js,segment.css,segment.min.css,shape.css,shape.js,shape.min.css,shape.min.js,sidebar.css,sidebar.js,sidebar.min.css,sidebar.min.js,site.css,site.js,site.min.css,site.min.js,slider.css,slider.js,slider.min.css,slider.min.js,state.js,state.min.js,statistic.css,statistic.min.css,step.css,step.min.css,sticky.css,sticky.js,sticky.min.css,sticky.min.js,tab.css,tab.js,tab.min.css,tab.min.js,table.css,table.min.css,text.css,text.min.css,toast.css,toast.js,toast.min.css,toast.min.js,transition.css,transition.js,transition.min.css,transition.min.js,visibility.js,visibility.min.js")},
       {"/superkraft/frontend/libs/formantic-ui/themes", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "basic,default,famfamfam,github,material", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/basic", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "assets", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/basic/assets", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "fonts", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/basic/assets/fonts", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "icons.woff,icons.woff2")},
       {"/superkraft/frontend/libs/formantic-ui/themes/default", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "assets", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/default/assets", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "fonts", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/default/assets/fonts", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "Lato-Bold.woff,Lato-Bold.woff2,Lato-BoldItalic.woff,Lato-BoldItalic.woff2,Lato-Italic.woff,Lato-Italic.woff2,Lato-Regular.woff,Lato-Regular.woff2,LatoLatin-Bold.woff,LatoLatin-Bold.woff2,LatoLatin-BoldItalic.woff,LatoLatin-BoldItalic.woff2,LatoLatin-Italic.woff,LatoLatin-Italic.woff2,LatoLatin-Regular.woff,LatoLatin-Regular.woff2,brand-icons.woff,brand-icons.woff2,icons.woff,icons.woff2,outline-icons.woff,outline-icons.woff2")},
       {"/superkraft/frontend/libs/formantic-ui/themes/famfamfam", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "assets", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/famfamfam/assets", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "images", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/famfamfam/assets/images", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "flags.png")},
       {"/superkraft/frontend/libs/formantic-ui/themes/github", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "assets", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/github/assets", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "fonts", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/github/assets/fonts", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "octicons.woff,octicons.woff2")},
       {"/superkraft/frontend/libs/formantic-ui/themes/material", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "assets", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/material/assets", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "fonts", "")},
       {"/superkraft/frontend/libs/formantic-ui/themes/material/assets/fonts", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "icons.woff,icons.woff2")},
       {"/superkraft/frontend/libs/helpers", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "colors.js,strings.js")},
       {"/superkraft/frontend/libs/jquery", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "dist,external,jquery-ui,src", "AUTHORS.txt,LICENSE.txt,bower.json,jquery.min.js,package.json")},
       {"/superkraft/frontend/libs/jquery/dist", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "jquery.js,jquery.min.js,jquery.min.map,jquery.slim.js,jquery.slim.min.js,jquery.slim.min.map")},
       {"/superkraft/frontend/libs/jquery/external", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sizzle", "")},
       {"/superkraft/frontend/libs/jquery/external/sizzle", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "dist", "LICENSE.txt")},
       {"/superkraft/frontend/libs/jquery/external/sizzle/dist", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sizzle.js,sizzle.min.js,sizzle.min.map")},
       {"/superkraft/frontend/libs/jquery/jquery-ui", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "external", "AUTHORS.txt,LICENSE.txt,index.html,jquery-ui.css,jquery-ui.js,jquery-ui.min.css,jquery-ui.min.js,jquery-ui.structure.css,jquery-ui.structure.min.css,package.json")},
       {"/superkraft/frontend/libs/jquery/jquery-ui/external", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "jquery", "")},
       {"/superkraft/frontend/libs/jquery/jquery-ui/external/jquery", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "jquery.js")},
       {"/superkraft/frontend/libs/jquery/src", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "ajax,attributes,core,css,data,deferred,deprecated,effects,event,exports,manipulation,queue,traversing,var", "ajax.js,attributes.js,callbacks.js,core.js,css.js,data.js,deferred.js,deprecated.js,dimensions.js,effects.js,event.js,jquery.js,manipulation.js,offset.js,queue.js,selector-native.js,selector-sizzle.js,selector.js,serialize.js,traversing.js,wrap.js")},
       {"/superkraft/frontend/libs/jquery/src/ajax", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "var", "jsonp.js,load.js,script.js,xhr.js")},
       {"/superkraft/frontend/libs/jquery/src/ajax/var", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "location.js,nonce.js,rquery.js")},
       {"/superkraft/frontend/libs/jquery/src/attributes", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "attr.js,classes.js,prop.js,support.js,val.js")},
       {"/superkraft/frontend/libs/jquery/src/core", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "var", "DOMEval.js,access.js,camelCase.js,init.js,isAttached.js,nodeName.js,parseHTML.js,parseXML.js,ready-no-deferred.js,ready.js,readyException.js,stripAndCollapse.js,support.js,toType.js")},
       {"/superkraft/frontend/libs/jquery/src/core/var", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "rsingleTag.js")},
       {"/superkraft/frontend/libs/jquery/src/css", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "var", "addGetHookIf.js,adjustCSS.js,curCSS.js,finalPropName.js,hiddenVisibleSelectors.js,showHide.js,support.js")},
       {"/superkraft/frontend/libs/jquery/src/css/var", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "cssExpand.js,getStyles.js,isHiddenWithinTree.js,rboxStyle.js,rnumnonpx.js,swap.js")},
       {"/superkraft/frontend/libs/jquery/src/data", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "var", "Data.js")},
       {"/superkraft/frontend/libs/jquery/src/data/var", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "acceptData.js,dataPriv.js,dataUser.js")},
       {"/superkraft/frontend/libs/jquery/src/deferred", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "exceptionHook.js")},
       {"/superkraft/frontend/libs/jquery/src/deprecated", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "ajax-event-alias.js,event.js")},
       {"/superkraft/frontend/libs/jquery/src/effects", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "Tween.js,animatedSelector.js")},
       {"/superkraft/frontend/libs/jquery/src/event", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "focusin.js,support.js,trigger.js")},
       {"/superkraft/frontend/libs/jquery/src/exports", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "amd.js,global.js")},
       {"/superkraft/frontend/libs/jquery/src/manipulation", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "var", "_evalUrl.js,buildFragment.js,getAll.js,setGlobalEval.js,support.js,wrapMap.js")},
       {"/superkraft/frontend/libs/jquery/src/manipulation/var", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "rscriptType.js,rtagName.js")},
       {"/superkraft/frontend/libs/jquery/src/queue", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "delay.js")},
       {"/superkraft/frontend/libs/jquery/src/traversing", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "var", "findFilter.js")},
       {"/superkraft/frontend/libs/jquery/src/traversing/var", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "dir.js,rneedsContext.js,siblings.js")},
       {"/superkraft/frontend/libs/jquery/src/var", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "ObjectFunctionString.js,arr.js,class2type.js,document.js,documentElement.js,flat.js,fnToString.js,getProto.js,hasOwn.js,indexOf.js,isFunction.js,isWindow.js,pnum.js,push.js,rcheckableType.js,rcssNum.js,rnothtmlwhite.js,slice.js,support.js,toString.js")},
       {"/superkraft/frontend/libs/js-cookie", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "js.cookie.min.js")},
       {"/superkraft/frontend/libs/jsom", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "jsom.css,jsom.js")},
       {"/superkraft/frontend/libs/progressbarjs", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "progressbar.min.js")},
       {"/superkraft/frontend/libs/sk_childMngr", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_childMngr.js")},
       {"/superkraft/frontend/libs/sk_comm", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_comm_core.js,sk_comm_dapp.js,sk_comm_japp.js,sk_comm_sapp.js,sk_comm_skxx.js,sk_comm_wapp.js")},
       {"/superkraft/frontend/libs/sk_commands", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_commands.js")},
       {"/superkraft/frontend/libs/sk_cursor", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_cursor.js")},
       {"/superkraft/frontend/libs/sk_dialog", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_dialog_core.js,sk_dialog_dapp.js,sk_dialog_wapp.js")},
       {"/superkraft/frontend/libs/sk_fileDrop", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_fileDrop.js")},
       {"/superkraft/frontend/libs/sk_hint", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_hint.js")},
       {"/superkraft/frontend/libs/sk_l10n", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_l10n.js")},
       {"/superkraft/frontend/libs/sk_mobile", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_mobile.js")},
       {"/superkraft/frontend/libs/sk_shortcuts", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_shortcuts.js")},
       {"/superkraft/frontend/libs/sk_titlebar", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_titlebar.css,sk_titlebar.js")},
       {"/superkraft/frontend/libs/sk_ums", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ums.js")},
       {"/superkraft/frontend/libs/sk_viewController", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_viewController.js")},
       {"/superkraft/frontend/libs/ua_parser", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "ua_parser.min.js")},
       {"/superkraft/modules", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_fs,sk_ipc", "sk_cdnExporter.js,sk_rootAction.js,sk_root_POST.js,sk_stats.js,sk_terminal.js,sk_timers.js,sk_ums.js,sk_utils.js,sk_validator.js")},
       {"/superkraft/modules/sk_fs", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_fs.js,sk_fs_juce.js,sk_fs_simple.js,sk_fs_skxx.js,sk_fs_ssc.js")},
       {"/superkraft/modules/sk_ipc", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ipc.js,sk_ipc_iPlug2.js,sk_ipc_juce.js")},
       {"/superkraft/ui", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "backend,frontend", "")},
       {"/superkraft/ui/backend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "head.ejs,script.ejs,sk_ui.js,sk_ui_fontMngr.js")},
       {"/superkraft/ui/frontend", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "core", "")},
       {"/superkraft/ui/frontend/core", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui_button,sk_ui_canvas,sk_ui_checkbox,sk_ui_checkmark,sk_ui_colorPicker,sk_ui_component,sk_ui_contextMenu,sk_ui_dappTitlebar,sk_ui_dropdown,sk_ui_eventBlocker,sk_ui_fileDrop_Area,sk_ui_group,sk_ui_groupCollapsable,sk_ui_hint,sk_ui_iceRink,sk_ui_icon,sk_ui_iconButton,sk_ui_image,sk_ui_infoLabel,sk_ui_input,sk_ui_l10n_selector,sk_ui_label,sk_ui_labelledSwitch,sk_ui_languageAndCurrencyDropdown,sk_ui_linkButton,sk_ui_list,sk_ui_loader,sk_ui_menu,sk_ui_miniActionBtn,sk_ui_modal,sk_ui_pixi_canvas,sk_ui_progressBar,sk_ui_prompter,sk_ui_rating,sk_ui_roundedBtn,sk_ui_ruler,sk_ui_segment,sk_ui_segmentField,sk_ui_separator,sk_ui_simpleActionBtn,sk_ui_simpleActionIconBtn,sk_ui_simpleButton,sk_ui_slider,sk_ui_spacer,sk_ui_statusIndicator,sk_ui_successMessage,sk_ui_svg,sk_ui_switch,sk_ui_table,sk_ui_text,sk_ui_textarea", "sk_ui.css,sk_ui_colors.css,sk_ui_gradients.css,sk_ui_shadows.css")},
       {"/superkraft/ui/frontend/core/sk_ui_button", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_button.css,sk_ui_button.js")},
       {"/superkraft/ui/frontend/core/sk_ui_canvas", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_canvas.css,sk_ui_canvas.js")},
       {"/superkraft/ui/frontend/core/sk_ui_checkbox", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_checkbox.css,sk_ui_checkbox.js")},
       {"/superkraft/ui/frontend/core/sk_ui_checkmark", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_checkmark.css,sk_ui_checkmark.js")},
       {"/superkraft/ui/frontend/core/sk_ui_colorPicker", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_colorPicker.css,sk_ui_colorPicker.js")},
       {"/superkraft/ui/frontend/core/sk_ui_component", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_component.css,sk_ui_component.js")},
       {"/superkraft/ui/frontend/core/sk_ui_contextMenu", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_contextMenu.css,sk_ui_contextMenu.js")},
       {"/superkraft/ui/frontend/core/sk_ui_dappTitlebar", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_dappTitlebar.css,sk_ui_dappTitlebar.js")},
       {"/superkraft/ui/frontend/core/sk_ui_dropdown", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_dropdown.css,sk_ui_dropdown.js")},
       {"/superkraft/ui/frontend/core/sk_ui_eventBlocker", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_eventBlocker.css,sk_ui_eventBlocker.js")},
       {"/superkraft/ui/frontend/core/sk_ui_fileDrop_Area", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_fileDrop_Area.css,sk_ui_fileDrop_Area.js")},
       {"/superkraft/ui/frontend/core/sk_ui_group", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_group.css,sk_ui_group.js")},
       {"/superkraft/ui/frontend/core/sk_ui_groupCollapsable", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_groupCollapsable.css,sk_ui_groupCollapsable.js")},
       {"/superkraft/ui/frontend/core/sk_ui_hint", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_hint.css,sk_ui_hint.js")},
       {"/superkraft/ui/frontend/core/sk_ui_iceRink", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_iceRink.css,sk_ui_iceRink.js")},
       {"/superkraft/ui/frontend/core/sk_ui_icon", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_icon.css,sk_ui_icon.js")},
       {"/superkraft/ui/frontend/core/sk_ui_iconButton", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_iconButton.css,sk_ui_iconButton.js")},
       {"/superkraft/ui/frontend/core/sk_ui_image", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_image.css,sk_ui_image.js")},
       {"/superkraft/ui/frontend/core/sk_ui_infoLabel", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_infoLabel.css,sk_ui_infoLabel.js")},
       {"/superkraft/ui/frontend/core/sk_ui_input", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_input.css,sk_ui_input.js")},
       {"/superkraft/ui/frontend/core/sk_ui_l10n_selector", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_l10n_selector.css,sk_ui_l10n_selector.js")},
       {"/superkraft/ui/frontend/core/sk_ui_label", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_label.css,sk_ui_label.js")},
       {"/superkraft/ui/frontend/core/sk_ui_labelledSwitch", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_labelledSwitch.css,sk_ui_labelledSwitch.js")},
       {"/superkraft/ui/frontend/core/sk_ui_languageAndCurrencyDropdown", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_languageAndCurrencyDropdown.css,sk_ui_languageAndCurrencyDropdown.js")},
       {"/superkraft/ui/frontend/core/sk_ui_linkButton", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_linkButton.css,sk_ui_linkButton.js")},
       {"/superkraft/ui/frontend/core/sk_ui_list", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "sk_ui_listItem", "sk_ui_list.css,sk_ui_list.js")},
       {"/superkraft/ui/frontend/core/sk_ui_list/sk_ui_listItem", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_listItem.css,sk_ui_listItem.js")},
       {"/superkraft/ui/frontend/core/sk_ui_loader", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_loader.css,sk_ui_loader.js")},
       {"/superkraft/ui/frontend/core/sk_ui_menu", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_menu.css,sk_ui_menu.js")},
       {"/superkraft/ui/frontend/core/sk_ui_miniActionBtn", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_miniActionBtn.css,sk_ui_miniActionBtn.js")},
       {"/superkraft/ui/frontend/core/sk_ui_modal", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_modal.css,sk_ui_modal.js")},
       {"/superkraft/ui/frontend/core/sk_ui_pixi_canvas", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_pixi_canvas.js")},
       {"/superkraft/ui/frontend/core/sk_ui_progressBar", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_progressBar.css,sk_ui_progressBar.js")},
       {"/superkraft/ui/frontend/core/sk_ui_prompter", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_prompter.css,sk_ui_prompter.js")},
       {"/superkraft/ui/frontend/core/sk_ui_rating", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_rating.css,sk_ui_rating.js")},
       {"/superkraft/ui/frontend/core/sk_ui_roundedBtn", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_roundedBtn.css,sk_ui_roundedBtn.js")},
       {"/superkraft/ui/frontend/core/sk_ui_ruler", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_ruler.css,sk_ui_ruler.js")},
       {"/superkraft/ui/frontend/core/sk_ui_segment", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_segment.css,sk_ui_segment.js")},
       {"/superkraft/ui/frontend/core/sk_ui_segmentField", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_segmentField.css,sk_ui_segmentField.js")},
       {"/superkraft/ui/frontend/core/sk_ui_separator", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_separator.css,sk_ui_separator.js")},
       {"/superkraft/ui/frontend/core/sk_ui_simpleActionBtn", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_simpleActionBtn.css,sk_ui_simpleActionBtn.js")},
       {"/superkraft/ui/frontend/core/sk_ui_simpleActionIconBtn", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_simpleActionIconBtn.css,sk_ui_simpleActionIconBtn.js")},
       {"/superkraft/ui/frontend/core/sk_ui_simpleButton", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_simpleButton.css,sk_ui_simpleButton.js")},
       {"/superkraft/ui/frontend/core/sk_ui_slider", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_slider.css,sk_ui_slider.js")},
       {"/superkraft/ui/frontend/core/sk_ui_spacer", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_spacer.css,sk_ui_spacer.js")},
       {"/superkraft/ui/frontend/core/sk_ui_statusIndicator", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_statusIndicator.css,sk_ui_statusIndicator.js")},
       {"/superkraft/ui/frontend/core/sk_ui_successMessage", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_successMessage.css,sk_ui_successMessage.js")},
       {"/superkraft/ui/frontend/core/sk_ui_svg", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_svg.css,sk_ui_svg.js")},
       {"/superkraft/ui/frontend/core/sk_ui_switch", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_switch.css,sk_ui_switch.js")},
       {"/superkraft/ui/frontend/core/sk_ui_table", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_table.css,sk_ui_table.js")},
       {"/superkraft/ui/frontend/core/sk_ui_text", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_text.css,sk_ui_text.js")},
       {"/superkraft/ui/frontend/core/sk_ui_textarea", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "sk_ui_textarea.css,sk_ui_textarea.js")},
       {"/test", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "libs", "")},
       {"/test/libs", new SK_SoftBackend_Bundle_Entry_Info(0, 0, 0, 0,0, true, "", "", "")}

    };

    SK_SoftBackend_Bundle_Entry_Info* findByPath(const SK_String& path) {
        auto fileEntry_Pair = fileEntries.find(path);
        auto folderEntry_Pair = folderEntries.find(path);

        if (fileEntry_Pair == fileEntries.end() && folderEntry_Pair == folderEntries.end()) return nullptr;

        SK_SoftBackend_Bundle_Entry_Info* entry = nullptr;
        
        if (fileEntry_Pair != fileEntries.end()){
            entry = fileEntry_Pair->second;
        }
        
        if (folderEntry_Pair != folderEntries.end()){
            entry = folderEntry_Pair->second;
        }
        
        return entry;
    };
};

END_SK_NAMESPACE
