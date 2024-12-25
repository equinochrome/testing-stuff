#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/font/lv_font.h"
#include "main.h"  // IWYU pragma: keep

int mogo1;
int mogo2;
int redblubuilder(1);
int posnegbuilder(3);
int goalrushbuilder(5);
bool allianceringbuilder(true);
bool useredblu = true;
bool useposneg = true;
bool usegoalrush = false;
int *rings;

vector<std::string> modules;

lv_obj_t *builderoverlay;
lv_obj_t *Mogo1;
lv_obj_t *Mogo1back;
lv_obj_t *Mogo2;
lv_obj_t *Mogo2back;
lv_obj_t *Pos;
lv_obj_t *Neg;
lv_obj_t *RedBlu;
lv_obj_t *AllianceRing;
lv_obj_t *GoalRush;
lv_obj_t *builderringind;
lv_obj_t *AutonBaseInfo;
lv_obj_t *AutonPathInfo;
lv_obj_t *AutonBaseInfoTxt;
lv_obj_t *AutonPathInfoTxt;

static lv_style_t styleindbuilder;
static lv_style_t styletextbuilder;

LV_IMG_DECLARE(autonbuilderoverlay);

void updatepath() {
	int finmogo1 = mogo1 > 0 ? mogo1 : mogo2;
	int finmogo2 = mogo1 > 0 ? mogo2 : 0;
	if((allianceringbuilder == true ? 1 : 0) + finmogo1 + finmogo2 > 10) finmogo2 -= ((allianceringbuilder == true ? 1 : 0) + finmogo1 + finmogo2 - 10);
	int singlesiter = 0;
	int doublesiter = 0;
	int cornersiter = 0;
	int usefinmogo1 = finmogo1;
	int usefinmogo2 = finmogo2;
	useredblu = redblubuilder == 0 ? true : false;
	useposneg = posnegbuilder == 3 ? true : false;
	usegoalrush = goalrushbuilder == 6 ? true : false;
	bool usemidtwo = useposneg;
	bool setside = true;
	std::string path;

	modules.clear();
	vector<std::string> singles{"left bottom ring", "mid top ring", "right bottom ring"};
	vector<std::string> doubles{"left corner", "right corner"};

	lv_label_set_text_fmt(AutonBaseInfoTxt, "Team: %s\nCorner: %s\nMogo 1: %d\nMogo 2: %d\nG.Rush: %s\nA.Stke: %s\nStart pos: %d inches", (useredblu == true ? "Red" : "Blue"),
						  (useposneg == true ? "Neg" : "Pos"), finmogo1, finmogo2, (usegoalrush == true ? "On" : "Off"),
						  (allianceringbuilder == true ? "On" : "Off"), usegoalrush == true ? (useredblu == useposneg ? 120 : 24) : (useredblu == useposneg ? 96 : 48));

	if(usegoalrush == true) modules.push_back("goal rush");
	if(allianceringbuilder == true) modules.push_back("alliance stake");

	if(usefinmogo1 > 0) {
		modules.push_back(usegoalrush == true ? (useredblu == useposneg ? "regrab goal rush right" : "regrab goal rush left") : (useredblu == useposneg ? "right mogo" : "left mogo"));
		setside = !(useredblu == useposneg);
		usemidtwo = useredblu == useposneg ? !setside : setside;
		for(int ringscore = 0; ringscore < usefinmogo1 - (allianceringbuilder == true ? 0 : 1); ringscore++) {
			if((finmogo1 - (allianceringbuilder == true ? 0 : 1)) % 2 == 0 && finmogo1 - (allianceringbuilder == true ? 0 : 1) != 0 && doublesiter < 3) {
				if((useposneg == false || usemidtwo == false) && cornersiter < 2) {
					modules.push_back(setside == true ? doubles.front() : doubles.back());
					doubles.erase(setside == true ? doubles.begin() : doubles.end());
					doubles.shrink_to_fit();
					cornersiter++;
					if((finmogo1 - (allianceringbuilder == true ? 2 : 3)) % 2 == 0 && finmogo1 - (allianceringbuilder == true ? 2 : 3) != 0 &&
					   doublesiter + 1 < 3)
						setside = !setside;
				} else if(usemidtwo == true || cornersiter >= 2) {
					modules.push_back(useredblu == true ? "red mid two" : "blue mid two");
					usemidtwo = false;
				}
				finmogo1 -= 2;
				doublesiter++;
			} else if((finmogo1 - (allianceringbuilder == true ? 0 : 1) != 0) && singlesiter < 3) {
				modules.push_back(setside == true ? singles.front() : singles.back());
				singles.erase(setside == true ? singles.begin() : singles.end());
				singles.shrink_to_fit();
				finmogo1--;
				singlesiter++;
			}
		}
	}

	if(usefinmogo2 > 0) {
		modules.push_back((useredblu == useposneg) == usegoalrush ? "right mogo" : "left mogo");
		setside = !(useredblu == useposneg) == usegoalrush;
		usemidtwo = useredblu == useposneg ? !setside : setside;
		for(int ringscore = 0; ringscore < usefinmogo2; ringscore++) {
			if((finmogo2) % 2 == 0 && finmogo2 != 0 && doublesiter < 3) {
				if((useposneg == false || usemidtwo == false) && cornersiter < 2) {
					modules.push_back(setside == true ? doubles.front() : doubles.back());
					doubles.erase(setside == true ? doubles.begin() : doubles.end());
					doubles.shrink_to_fit();
					cornersiter++;
					if((finmogo2 - 2) % 2 == 0 && finmogo2 - 2 != 0 && doublesiter + 1 < 3) setside = !setside;
				} else if(usemidtwo == true || cornersiter >= 2) {
					modules.push_back(useredblu == true ? "red mid two" : "blue mid two");
					usemidtwo = false;
				}
				finmogo2 -= 2;
				doublesiter++;
			} else if((finmogo2 != 0) && singlesiter < 3) {
				modules.push_back(setside == true ? singles.front() : singles.back());
				singles.erase(setside == true ? singles.begin() : singles.end());
				singles.shrink_to_fit();
				finmogo2--;
				singlesiter++;
			}
		}
	}

	modules.push_back("ladder");

	for(int strings = 0; strings < modules.size(); strings++) {
		path = path.append(modules[strings]) + "\n";
	}

	lv_label_set_text_fmt(AutonPathInfoTxt, "%s", path.c_str());
}

static void mogopress(lv_event_t *e) {
	lv_obj_t *target = lv_event_get_target(e);
	target == Mogo1 || target == Mogo1back ? rings = &mogo1 : rings = &mogo2;
	*rings = (*rings + 1) % 7;
	lv_obj_set_size(Mogo1, 67, 108 - (18 * mogo1));
	lv_obj_set_size(Mogo2, 67, 108 - (18 * mogo2));

	updatepath();
}

static void specify(lv_event_t *e) {
	lv_obj_t *target = lv_event_get_target(e);

	if(target == RedBlu) redblubuilder == 0 ? redblubuilder = 1 : redblubuilder = 0;
	if(target == AllianceRing) allianceringbuilder == false ? allianceringbuilder = true : allianceringbuilder = false;
	if(target == GoalRush && posnegbuilder == 4) {
		goalrushbuilder == 5 ? goalrushbuilder = 6 : goalrushbuilder = 5;
	}

	if(target == Pos) {
		posnegbuilder = 4;
		lv_obj_set_style_bg_color(Neg, colortable[5], LV_PART_MAIN);
		lv_obj_set_style_bg_color(Pos, colortable[posnegbuilder], LV_PART_MAIN);
		lv_obj_set_style_bg_opa(GoalRush, 255, LV_PART_MAIN);
	}
	if(target == Neg) {
		posnegbuilder = 3;
		lv_obj_set_style_bg_color(Pos, colortable[5], LV_PART_MAIN);
		lv_obj_set_style_bg_color(Neg, colortable[posnegbuilder], LV_PART_MAIN);
		lv_obj_set_style_bg_opa(GoalRush, 0, LV_PART_MAIN);
		goalrushbuilder = 5;
	}

	lv_obj_set_style_bg_color(RedBlu, colortable[redblubuilder], LV_PART_MAIN);
	lv_obj_set_style_bg_color(Mogo1back, colortable[redblubuilder], LV_PART_MAIN);
	lv_obj_set_style_bg_color(Mogo2back, colortable[redblubuilder], LV_PART_MAIN);
	lv_obj_set_style_bg_color(GoalRush, colortable[goalrushbuilder], LV_PART_MAIN);
	allianceringbuilder == true ? lv_obj_set_style_bg_opa(AllianceRing, 0, LV_PART_MAIN) : lv_obj_set_style_bg_opa(AllianceRing, 255, LV_PART_MAIN);

	updatepath();
}

static void getinfo(lv_event_t * e) {
	lv_obj_t * target = lv_event_get_current_target(e);
	lv_obj_t * autonbuildinfo = lv_msgbox_create(NULL, (target == AutonBaseInfo ? "selection info:" : "path info:"), lv_label_get_text(target == AutonBaseInfo ? AutonBaseInfoTxt : AutonPathInfoTxt), NULL, true);
	lv_obj_add_style(autonbuildinfo, &styletextbuilder, LV_PART_MAIN);
	lv_obj_add_style(lv_msgbox_get_close_btn(autonbuildinfo), &styletextbuilder, LV_PART_MAIN);

	lv_obj_set_style_border_opa(lv_msgbox_get_close_btn(autonbuildinfo), 0, LV_PART_MAIN);
	
	lv_obj_set_style_text_font(lv_msgbox_get_close_btn(autonbuildinfo), &lv_font_montserrat_20, LV_PART_MAIN);
	lv_obj_set_style_text_font(autonbuildinfo, &pros_font_dejavu_mono_18, LV_PART_MAIN);

	lv_obj_align(autonbuildinfo, LV_ALIGN_CENTER, 0, 0);
}

lv_event_cb_t mogoPress = mogopress;
lv_event_cb_t Specify = specify;
lv_event_cb_t getInfo = getinfo;

void autonbuilderinit() {
	builderoverlay = lv_img_create(autobuilder);
	Mogo1 = lv_btn_create(autobuilder);
	Mogo1back = lv_btn_create(autobuilder);
	Mogo2 = lv_btn_create(autobuilder);
	Mogo2back = lv_btn_create(autobuilder);
	Pos = lv_btn_create(autobuilder);
	Neg = lv_btn_create(autobuilder);
	RedBlu = lv_btn_create(autobuilder);
	AllianceRing = lv_btn_create(autobuilder);
	GoalRush = lv_btn_create(autobuilder);
	builderringind = lv_obj_create(autobuilder);
	AutonBaseInfo = lv_obj_create(autobuilder);
	AutonPathInfo = lv_obj_create(autobuilder);
	AutonBaseInfoTxt = lv_label_create(AutonBaseInfo);
	AutonPathInfoTxt = lv_label_create(AutonPathInfo);

	lv_style_init(&styleindbuilder);
	lv_style_set_border_width(&styleindbuilder, 0);
	lv_style_set_radius(&styleindbuilder, 0);
	lv_style_set_transform_width(&styleindbuilder, 0);
	lv_style_set_transform_height(&styleindbuilder, 0);

	lv_style_init(&styletextbuilder);
	lv_style_set_border_color(&styletextbuilder, lv_color_hex(0xcfffe9));
	lv_style_set_border_width(&styletextbuilder, 2);
	lv_style_set_radius(&styletextbuilder, 0);
	lv_style_set_text_color(&styletextbuilder, lv_color_hex(0xcfffe9));
	lv_style_set_bg_color(&styletextbuilder, lv_color_hex(0x071808));
	lv_style_set_bg_opa(&styletextbuilder, 255);
	lv_style_set_text_font(&styletextbuilder, &pros_font_dejavu_mono_10);
	lv_style_set_pad_all(&styletextbuilder, 2);

	lv_img_set_src(builderoverlay, &autonbuilderoverlay);

	lv_obj_set_pos(Mogo1, 49, 90);
	lv_obj_set_pos(Mogo1back, 49, 90);
	lv_obj_set_pos(Mogo2, 364, 90);
	lv_obj_set_pos(Mogo2back, 364, 90);
	lv_obj_set_pos(Pos, 142, 69);
	lv_obj_set_pos(Neg, 290, 88);
	lv_obj_set_pos(RedBlu, 204, 13);
	lv_obj_set_pos(AllianceRing, 204, 59);
	lv_obj_set_pos(GoalRush, 216, 153);
	lv_obj_set_pos(builderringind, 220, 100);
	lv_obj_set_pos(AutonBaseInfo, 129, 128);
	lv_obj_set_pos(AutonPathInfo, 264, 128);

	lv_obj_set_size(Mogo1, 67, 105);
	lv_obj_set_size(Mogo1back, 67, 105);
	lv_obj_set_size(Mogo2, 67, 105);
	lv_obj_set_size(Mogo2back, 67, 105);
	lv_obj_set_size(Pos, 48, 48);
	lv_obj_set_size(Neg, 48, 11);
	lv_obj_set_size(RedBlu, 72, 74);
	lv_obj_set_size(AllianceRing, 72, 17);
	lv_obj_set_size(GoalRush, 48, 73);
	lv_obj_set_size(builderringind, 40, 40);
	lv_obj_set_size(AutonBaseInfo, 87, 65);
	lv_obj_set_size(AutonPathInfo, 87, 65);

	lv_obj_add_style(Mogo1, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(Mogo1back, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(Mogo2, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(Mogo2back, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(Mogo1, &styleindbuilder, LV_STATE_PRESSED);
	lv_obj_add_style(Mogo1back, &styleindbuilder, LV_STATE_PRESSED);
	lv_obj_add_style(Mogo2, &styleindbuilder, LV_STATE_PRESSED);
	lv_obj_add_style(Mogo2back, &styleindbuilder, LV_STATE_PRESSED);
	lv_obj_add_style(Pos, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(Neg, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(RedBlu, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(AllianceRing, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(GoalRush, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(builderringind, &styleindbuilder, LV_PART_MAIN);
	lv_obj_add_style(AutonBaseInfo, &styletextbuilder, LV_PART_MAIN);
	lv_obj_add_style(AutonPathInfo, &styletextbuilder, LV_PART_MAIN);

	lv_obj_clear_flag(AutonBaseInfo, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_clear_flag(AutonPathInfo, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_add_flag(AutonBaseInfo, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(AutonPathInfo, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(AutonBaseInfoTxt, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(AutonPathInfoTxt, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(AutonBaseInfoTxt, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(AutonPathInfoTxt, LV_OBJ_FLAG_EVENT_BUBBLE);

	lv_obj_set_style_bg_color(Mogo1, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
	lv_obj_set_style_bg_color(Mogo2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
	lv_obj_set_style_bg_color(AllianceRing, lv_color_hex(0x5d5d5d), LV_PART_MAIN);

	lv_obj_set_style_border_width(AutonBaseInfo, 4, LV_STATE_PRESSED);
	lv_obj_set_style_border_width(AutonPathInfo, 4, LV_STATE_PRESSED);

	lv_obj_move_background(Mogo1back);
	lv_obj_move_background(Mogo2back);

	lv_obj_add_event_cb(Mogo1, mogoPress, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(Mogo1back, mogoPress, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(Mogo2, mogoPress, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(Mogo2back, mogoPress, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(Pos, Specify, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(Neg, Specify, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(RedBlu, Specify, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(AllianceRing, Specify, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(GoalRush, Specify, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(AutonBaseInfo, getInfo, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(AutonPathInfo, getInfo, LV_EVENT_CLICKED, NULL);

	lv_obj_move_foreground(Mogo1);
	lv_obj_move_foreground(Mogo2);
	lv_obj_move_foreground(AllianceRing);
	lv_obj_move_foreground(builderoverlay);
	lv_obj_move_foreground(AutonBaseInfo);
	lv_obj_move_foreground(AutonPathInfo);

	lv_event_send(RedBlu, LV_EVENT_CLICKED, NULL);
	lv_event_send(Neg, LV_EVENT_CLICKED, NULL);
	lv_event_send(AllianceRing, LV_EVENT_CLICKED, NULL);
}