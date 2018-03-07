#include "GuiTheme.h"

GuiTheme::GuiTheme()
{
	layout.labelWidth = 130;


	float scale = 1.5;
	font.size *= scale;
	stripe.width *= scale;
	layout.width *= scale;
	layout.height *= scale;
	layout.breakHeight = 40 * scale; 
	layout.padding *= scale;
	layout.vMargin *= scale;
	layout.vMargin = ceilf(layout.vMargin);
	layout.iconSize *= scale;
	layout.labelWidth *= scale;
	layout.labelMargin *= scale;
	layout.graph.height *= scale;
	layout.pad2d.height *= scale;
	layout.pad2d.ballSize *= scale;
	layout.pad2d.lineWeight *= scale;
	layout.matrix.height *= scale;
	layout.matrix.buttonSize *= scale;
	layout.matrix.buttonPadding *= scale;
	layout.colorPicker.rainbowWidth *= scale;
	layout.textInput.highlightPadding *= scale;

	init();
}


GuiTheme::~GuiTheme()
{
}
