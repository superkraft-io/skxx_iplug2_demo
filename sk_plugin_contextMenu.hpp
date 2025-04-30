#pragma once

#include "IPlugPlatform.h"
#include "IGraphicsPopupMenu.h"

using namespace iplug;

class SK_Plugin_ContextMenu {
public:
    iplug::igraphics::IPopupMenu popupMenu;

    SK_Plugin_ContextMenu() {

    }

    void popup(int paramIdx, int x, int y){
        iplug::igraphics::IPopupMenu& contextMenu = popupMenu;
  contextMenu.Clear();

  if(pControl)
  {
    pControl->CreateContextMenu(contextMenu);

#if defined VST3_API || defined VST3C_API
    VST3_API_BASE* pVST3 = dynamic_cast<VST3_API_BASE*>(GetDelegate());

    if (!pVST3->GetComponentHandler() || !pVST3->GetView())
      return;

    Steinberg::FUnknownPtr<Steinberg::Vst::IComponentHandler3>handler(pVST3->GetComponentHandler() );

    if (handler == 0)
      return;

    Steinberg::Vst::ParamID p = paramIdx;

    Steinberg::Vst::IContextMenu* pVST3ContextMenu = handler->createContextMenu(pVST3->GetView(), &p);

    if (pVST3ContextMenu)
    {
      std::function<void(IPopupMenu* pCurrentMenu)> populateFunc;
      Steinberg::int32 tag = 0;
      
      populateFunc = [&populateFunc, &tag, pVST3ContextMenu, pControl](IPopupMenu* pCurrentMenu) {
        Steinberg::Vst::IContextMenu::Item item = {0};

        for (int i = 0; i < pCurrentMenu->NItems(); i++)
        {
          Steinberg::UString128 (pCurrentMenu->GetItemText(i)).copyTo (item.name, 128);
          item.tag = tag++;
          item.flags = 0;
          
          if (pCurrentMenu->GetItem(i)->GetIsSeparator())
          {
            item.flags = Steinberg::Vst::IContextMenu::Item::kIsSeparator;
          }
          else if (auto pSubMenu = pCurrentMenu->GetItem(i)->GetSubmenu())
          {
            item.flags = Steinberg::Vst::IContextMenu::Item::kIsGroupStart;
            pVST3ContextMenu->addItem(item, pControl);
            populateFunc(pSubMenu);
            item.tag = tag++;
            item.flags = Steinberg::Vst::IContextMenu::Item::kIsGroupEnd;
            pVST3ContextMenu->addItem(item, pControl);
            continue;
          }
          else
          {
            if (!pCurrentMenu->GetItem(i)->GetEnabled())
              item.flags |= Steinberg::Vst::IContextMenu::Item::kIsDisabled;
            
            if (pCurrentMenu->GetItem(i)->GetChecked())
              item.flags |= Steinberg::Vst::IContextMenu::Item::kIsChecked;
          }
          
          pVST3ContextMenu->addItem(item, pControl);
        }
      };
      
      populateFunc(&contextMenu);
     
#ifdef OS_WIN
      x *= GetTotalScale();
      y *= GetTotalScale();
#else
      x *= GetDrawScale();
      y *= GetDrawScale();
#endif
      pVST3ContextMenu->popup((Steinberg::UCoord) x, (Steinberg::UCoord) y);
      pVST3ContextMenu->release();
    }

#else
    if(!contextMenu.NItems())
      return;

    DoCreatePopupMenu(*pControl, contextMenu, IRECT(x, y, x, y), kNoValIdx, true);
#endif
  }
    }
};
