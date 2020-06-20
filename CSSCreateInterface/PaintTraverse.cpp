#include "Hooks.h"
#include "SetupHack.h"
#include <mutex>
#include "Global.h"
PaintTraverseFn oPaintTraverse;

void __stdcall Hooks::HookPaintTraverse(int VGUIPanel, bool ForceRepaint, bool AllowForce)
{
	//std::lock_guard<std::recursive_mutex> lock(MutexLock::gMutex);

	oPaintTraverse(Interface->Panel, VGUIPanel, ForceRepaint, AllowForce);
	{ // So we only render on 1 panel.
		static int drawPanel = 0;
		if (!drawPanel)
			if (!strcmp(Interface->Panel->GetName(VGUIPanel), "MatSystemTopPanel"))
				drawPanel = VGUIPanel;
			else
				return;
		if (drawPanel != VGUIPanel)
			return;
	}

	MutexLock::gMutex.lock();
	SetupHack::GetViewMatrix();
	MutexLock::gMutex.unlock();

}