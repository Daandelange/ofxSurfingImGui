#include "ofxSurfing_ImGui_LayoutManager.h"

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::ofxSurfing_ImGui_Manager() {

	params_Advanced.add(bAdvanced);
	params_Advanced.add(bAutoResize);
	params_Advanced.add(bExtra);
	params_Advanced.add(bMinimize);

	// must be here to allow to be changed before setup!
	//// EXAMPLE
	//guiManager.setImGuiAutodraw(true);
	//guiManager.setup(); // this instantiates and configurates ofxImGui inside the class object.

	// -> TODO: BUG?: 
	// it seems than requires to be false when using multi-context/instances
	// if is setted to true, sometimes it hangs and gui do not refresh/freezes.
	bAutoDraw = false;

	//bAutoDraw = true;
	//if(bAutoSaveSettings) loadGroup(params_AppSettings, path_Settings);
};

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::~ofxSurfing_ImGui_Manager() {
};

//--

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup() { // using internal instantiated gui
	setup_ImGui();

	if (bAutoSaveSettings) loadGroup(params_AppSettings, path_Settings);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup(ofxImGui::Gui & _gui) { // using external instantiated gui
	guiPtr = &_gui;

	setup_ImGui();
}

//----

// fonts

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setDefaultFontIndex(int index)
{
	if (customFonts.size() == 0) return;

	currFont = ofClamp(index, 0, customFonts.size() - 1);
	customFont = customFonts[currFont];
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setDefaultFont()
{
	setDefaultFontIndex(0);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::pushFont(std::string path, int size)
{
	//TODO:
	// should be a vector with several customFont to allow hot reloading..
	// if not, last added font will be used
	ofLogNotice(__FUNCTION__) << path << ":" << size;

	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	ofFile fileToRead(path); // a file that exists
	bool b = fileToRead.exists();
	if (b)
	{
		ImFont* _customFont = nullptr;
		if (guiPtr != nullptr) {
			_customFont = guiPtr->addFont(path, size, nullptr, normalCharRanges);
		}
		else {
			_customFont = gui.addFont(path, size, nullptr, normalCharRanges);
		}

		if (_customFont != nullptr)
		{
			customFonts.push_back(_customFont);
			customFont = _customFont;
			currFont = customFonts.size() - 1;
		}
	}
	if (customFont != nullptr) io.FontDefault = customFont;

	return b;
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::addFont(std::string path, int size)
{
	//TODO:
	// should be a vector with several customFont to allow hot reloading..
	// if not, last added font will be used

	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	ofFile fileToRead(path); // a file that exists
	bool b = fileToRead.exists();
	if (b)
	{
		if (guiPtr != nullptr) customFont = guiPtr->addFont(path, size, nullptr, normalCharRanges);
		else customFont = gui.addFont(path, size, nullptr, normalCharRanges);
	}

	if (customFont != nullptr) io.FontDefault = customFont;

	return b;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::pushStyleFont(int index)
{
	if (index <= customFonts.size() - 1)
	{
		if (customFonts[index] != nullptr)
			ImGui::PushFont(customFonts[index]);
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::popStyleFont()
{
	ImGui::PopFont();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::processOpenFileSelection(ofFileDialogResult openFileResult, int size = 10) {

	string path = openFileResult.getPath();

	ofLogNotice(__FUNCTION__) << "getName(): " << openFileResult.getName();
	ofLogNotice(__FUNCTION__) << "getPath(): " << path;

	ofFile file(path);

	if (file.exists())
	{
		ofLogNotice(__FUNCTION__) << ("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		//We only want images
		if (fileExtension == "TTF" || fileExtension == "OTF") {

			ofLogNotice(__FUNCTION__) << ("TTF or OTF found!");

			pushFont(path, size);
		}
		else ofLogError(__FUNCTION__) << ("TTF or OTF not found!");
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::openFileFont(int size)
{
	//Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a font file, ttf or otf to add to ImGui", false, ofToDataPath(""));

	//Check if the user opened a file
	if (openFileResult.bSuccess) {

		ofLogNotice(__FUNCTION__) << ("User selected a file");

		//We have a file, check it and process it
		processOpenFileSelection(openFileResult, size);

	}
	else {
		ofLogNotice(__FUNCTION__) << ("User hit cancel");
	}
}

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup_ImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_None;

	bool bRestore = true;
	bool bMouse = false;

	if (bDocking) flags += ImGuiConfigFlags_DockingEnable;
	if (bViewport) flags += ImGuiConfigFlags_ViewportsEnable;

	// Setup imgui with the appropriate config flags
	if (guiPtr != nullptr) guiPtr->setup(nullptr, bAutoDraw, flags, bRestore, bMouse);
	else gui.setup(nullptr, bAutoDraw, flags, bRestore, bMouse);

	// Uncomment below to perform docking with SHIFT key
	// Gives a better user experience, matter of opinion.
	if (bDocking) ImGui::GetIO().ConfigDockingWithShift = true;

	// Uncomment below to "force" all imgui windows to be standalone
	//ImGui::GetIO().ConfigViewportsNoAutoMerge=true;

	//-

	//TODO: crashes if font not present!

	// font
	std::string _fontName;
	float _fontSizeParam;
	_fontName = "telegrama_render.otf"; // WARNING: will crash if font not present!
	_fontSizeParam = 11;
	std::string _path = "assets/fonts/"; // assets folder

	pushFont(_path + _fontName, _fontSizeParam); // queue default font too

	addFont(_path + _fontName, _fontSizeParam);

	//// extra fonts
	//addFont(_path + "OpenSans-Light.ttf", 16);
	//addFont(_path + "OpenSans-Regular.ttf", 16);
	//addFont(_path + "OpenSans-Light.ttf", 32);
	//addFont(_path + "OpenSans-Regular.ttf", 11);
	//addFont(_path + "OpenSans-Bold.ttf", 11);

	//-

	// theme
	//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing();
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::draw() {
	if (customFont == nullptr) gui.draw();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::begin() {
	if (guiPtr != nullptr) guiPtr->begin();
	else gui.begin();

	if (customFont != nullptr) ImGui::PushFont(customFont);

	//TODO:
	setDefaultFont();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh)); // minimal size

	//-

	// docking
	if (bDocking && bDockingModeCentered)
	{
		ImGuiDockNodeFlags dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode; // Make the docking space transparent
		ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, dockingFlags); // Also draws the docked windows

		ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);
		if (dockNode)
		{
			ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);

			// debug scene viewport
			if (bPreviewSceneViewport)
			{
				// Verifies if the central node is empty (visible empty space for oF)
				if (centralNode && centralNode->IsEmpty()) {
					ImRect availableSpace = centralNode->Rect();
					//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
					ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

					ImVec2 viewCenter = availableSpace.GetCenter();
					// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
					if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());
					ofPushStyle();
					ofSetRectMode(OF_RECTMODE_CENTER);
					ofSetColor(255, 0, 0, 2);
					ofNoFill();

					ofDrawRectangle(
						viewCenter.x,
						viewCenter.y,
						availableSpace.GetSize().x - 6,
						availableSpace.GetSize().y - 6
					);
					//ofNoFill();
					//ofSetColor(255, 255, 255, 30);
					//ofDrawRectangle(
					//	(viewCenter.x),
					//	(viewCenter.y),
					//	(availableSpace.GetSize().x - 20)*fmodf(abs(sin(ofGetElapsedTimef())), 1.f),
					//	(availableSpace.GetSize().y - 20)*fmodf(abs(sin(ofGetElapsedTimef())), 1.f)
					//);
					ofSetRectMode(OF_RECTMODE_CORNER);
					ofPopStyle();
				}
			}
		}
	}

	//-

	resetIDs(); // reset names
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::end() {

	ImGui::PopStyleVar(); // minimal size

	if (customFont != nullptr) ImGui::PopFont();

	// mouse lockers
	bMouseOverGui = false;
	bMouseOverGui = bMouseOverGui | ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
	bMouseOverGui = bMouseOverGui | ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
	bMouseOverGui = bMouseOverGui | ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);

	if (guiPtr != nullptr) guiPtr->end();
	else gui.end();
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(string name)
{
	return beginWindow(name, NULL, ImGuiWindowFlags_None);
}
//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(std::string name, bool* p_open) {
	return beginWindow(name, p_open, ImGuiWindowFlags_None);
}
//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(ofParameter<bool> p)
{
	return beginWindow(p.getName().c_str(), (bool*)&p.get(), ImGuiWindowFlags_None);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(ofParameter<bool> p, ImGuiWindowFlags window_flags)
{
	return beginWindow(p.getName().c_str(), (bool*)&p.get(), window_flags);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(string name = "Window", bool* p_open = NULL, ImGuiWindowFlags window_flags = ImGuiWindowFlags_None)
{
	//static bool no_close = true;
	//if (no_close) p_open = NULL; // Don't pass our bool* to Begin

	// force
	//window_flags |= ImGuiWindowFlags_NoDecoration;

	////widgets sizes
	//float _spcx;
	//float _spcy;
	//float _w100;
	//float _h100;
	//float _w99;
	//float _w50;
	//float _w33;
	//float _w25;
	//float _h;
	//ofxSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

	// bAutoResize mode
	//static bool bAutoResize = true;

	// minimal sizes
	//float ww = PANEL_WIDGETS_WIDTH_MIN;
	//float hh = PANEL_WIDGETS_HEIGHT_MIN;
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));

	//// Demonstrate the various window flags. Typically you would just use the default!
	//static bool no_titlebar = false;
	//static bool no_scrollbar = false;
	//static bool no_menu = false;
	//static bool no_move = false;
	//static bool no_resize = false;
	//static bool no_collapse = false;
	//static bool no_nav = false;
	//static bool no_background = false;
	//static bool no_bring_to_front = false;
	//static bool no_docking = false;

	////ImGuiWindowFlags window_flags = false;
	//if (bAutoResize)        window_flags |= ImGuiWindowFlags_AlwaysAutoResize;//not working, not ending expands..
	//if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	//if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	//if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	//if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	//if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	//if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	//if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	//if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	//if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;

	//-

	//// We specify a default position/size in case there's no data in the .ini file.
	//// We only do it to make the demo applications a little more welcoming, but typically this isn't required.
	//const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	// Main body of the Demo window starts here.
	bool b = ImGui::Begin(name.c_str(), p_open, window_flags);
	//if (!b)
	//{
	//	//// Early out if the window is collapsed, as an optimization.
	//	//ImGui::End();
	//	//return;
	//}

	// refresh layout
	widgetsManager.refresh();

	// set default font
	setDefaultFont();

	// Leave a fixed amount of width for labels (by passing a negative value), the rest goes to widgets.
	//ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	return b;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::endWindow()
{
	//ImGui::PopItemWidth();
	//ImGui::PopStyleVar();

	ImGui::End();
}
