#include "glgui.h"

static WHandle handle_index = 0;

WHandle new_glgui_handle()
{
	handle_index++;
	return handle_index;
}