#include "include.h"
#include "Hooks.h"
#include "Tools.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Global.h"

EndSceneFn oEndScene;

bool yes = true;

bool bInit;
void __stdcall Hooks::EndScene(IDirect3DDevice9* Device)
{
	if (bInit == false)
	{
		bInit = true;
	}

	if(Controller::windowVisible)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		/*Menu rendering here*/
		ImGui::Begin("Hello World", &yes);
		ImGui::ShowTestWindow(); // Oneshot has some good tutorials on how to do what
		/*Menu rendering here*/

		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	
	
	Tools::DrawString(800 + 1, 10 + 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800 + 1, 10 - 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800 - 1, 10 - 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800 - 1, 10 + 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800, 10, 230, 0, 230, "為美好的世界獻上祝福");

	return oEndScene(Device);
}