// A2DD.h
#ifndef ui_node
#define ui_node

#include <map>
#include <vector> // TODO: this has to be removed once UiArea classes
#include "nbind/api.h"
// declarations are moved to their own cc files

#define DEFINE_EVENT(NAME)                                                     \
  private:                                                                     \
	nbind::cbFunction *NAME##Callback = NULL;                                  \
                                                                               \
  public:                                                                      \
	void NAME(nbind::cbFunction &cb);

#define IMPLEMENT_EVENT(CLASS, WIDGET, NAME, LIBUI_FUN)                        \
	static void CLASS##_##NAME(WIDGET *w, void *data) {                        \
		nbind::cbFunction *cb = (nbind::cbFunction *)data;                     \
		(*cb)();                                                               \
	}                                                                          \
	void CLASS::NAME(nbind::cbFunction &cb) {                                  \
		NAME##Callback = new nbind::cbFunction(cb);                            \
		LIBUI_FUN((WIDGET *)getHandle(), CLASS##_##NAME, NAME##Callback);      \
	}

#define DEFINE_CONTROL_METHODS()                                               \
	void destroy();                                                            \
	void setParent(UiControl *parent);                                         \
	bool toplevel();                                                           \
	bool getVisible();                                                         \
	void setVisible(bool visible);                                             \
	bool getEnabled();                                                         \
	void setEnabled(bool enabled);

#define INHERITS_CONTROL_METHODS(CLASS)                                        \
	void CLASS::destroy() {                                                    \
		UiControl::destroy();                                                  \
	}                                                                          \
	void CLASS::setParent(UiControl *parent) {                                 \
		UiControl::setParent(parent);                                          \
	}                                                                          \
	bool CLASS::toplevel() {                                                   \
		return UiControl::toplevel();                                          \
	}                                                                          \
	bool CLASS::getVisible() {                                                 \
		return UiControl::getVisible();                                        \
	}                                                                          \
	void CLASS::setVisible(bool visible) {                                     \
		UiControl::setVisible(visible);                                        \
	}                                                                          \
	bool CLASS::getEnabled() {                                                 \
		return UiControl::getEnabled();                                        \
	}                                                                          \
	void CLASS::setEnabled(bool enabled) {                                     \
		UiControl::setEnabled(enabled);                                        \
	}

#define DECLARE_CHILD_CONTROL_METHODS()                                        \
	inherit(UiControl);                                                        \
	method(destroy);                                                           \
	method(setParent);                                                         \
	method(toplevel);                                                          \
	method(getVisible);                                                        \
	method(setVisible);                                                        \
	method(getEnabled);                                                        \
	method(setEnabled);                                                        \
	getset(getVisible, setVisible);                                            \
	getset(getEnabled, setEnabled);

#define DECLARE_CONTROL_METHODS()                                              \
	method(destroy);                                                           \
	method(setParent);                                                         \
	method(toplevel);                                                          \
	method(getVisible);                                                        \
	method(setVisible);                                                        \
	method(getEnabled);                                                        \
	method(setEnabled);                                                        \
	getset(getVisible, setVisible);                                            \
	getset(getEnabled, setEnabled);

#define DEFINE_ENTRY_METHODS()                                                 \
	void setText(const char *text);                                            \
	const char *getText();                                                     \
	void setReadOnly(bool readOnly);                                           \
	bool getReadOnly();

#define INHERITS_ENTRY_METHODS(CLASS)                                          \
	void CLASS::setText(const char *text) {                                    \
		UiEntryBase::setText(text);                                            \
	}                                                                          \
	const char *CLASS::getText() {                                             \
		return UiEntryBase::getText();                                         \
	}                                                                          \
	void CLASS::setReadOnly(bool readOnly) {                                   \
		UiEntryBase::setReadOnly(readOnly);                                    \
	}                                                                          \
	bool CLASS::getReadOnly() {                                                \
		return UiEntryBase::getReadOnly();                                     \
	}                                                                          \
	void CLASS::onChanged(nbind::cbFunction &cb) {                             \
		UiEntryBase::onChanged(cb);                                            \
	}

#define DECLARE_ENTRY_METHODS()                                                \
	getset(getText, setText);                                                  \
	getset(getReadOnly, setReadOnly);                                          \
	method(onChanged);                                                         \
	method(getText);                                                           \
	method(setText);                                                           \
	method(getReadOnly);                                                       \
	method(setReadOnly);

#define DEFINE_BOX_METHODS()                                                   \
	void append(UiControl *control, bool stretchy);                            \
	void deleteAt(int index);                                                  \
	bool getPadded();                                                          \
	void setPadded(bool padded);

#define INHERITS_BOX_METHODS(CLASS)                                            \
	void CLASS::append(UiControl *control, bool stretchy) {                    \
		UiBox::append(control, stretchy);                                      \
	}                                                                          \
	void CLASS::deleteAt(int index) {                                          \
		UiBox::deleteAt(index);                                                \
	}                                                                          \
	bool CLASS::getPadded() {                                                  \
		return UiBox::getPadded();                                             \
	}                                                                          \
	void CLASS::setPadded(bool padded) {                                       \
		UiBox::setPadded(padded);                                              \
	}

#define DECLARE_BOX_METHODS()                                                  \
	getset(getPadded, setPadded);                                              \
	method(getPadded);                                                         \
	method(setPadded);                                                         \
	method(append);                                                            \
	method(deleteAt);

class UiControl {
  private:
	uiControl *handle;

  public:
	uiControl *getHandle();
	UiControl(uiControl *hnd);
	DEFINE_CONTROL_METHODS()
};

class Point {
  private:
	int x;
	int y;

  public:
	Point(const Point &other);
	Point(int x, int y);
	int getX();
	void setX(int value);
	int getY();
	void setY(int value);
	void toJS(nbind::cbOutput output);
};

class Size {
  private:
	int w;
	int h;

  public:
	Size(int w, int h);
	int getWidth();
	void setWidth(int value);
	int getHeight();
	void setHeight(int value);
	void toJS(nbind::cbOutput output);
};

class PointDouble {
  private:
	double x;
	double y;

  public:
	PointDouble(double x, double y);
	PointDouble(const PointDouble &other);
	double getX();
	void setX(double value);
	double getY();
	void setY(double value);
	void toJS(nbind::cbOutput output);
};

class SizeDouble {
  private:
	double w;
	double h;

  public:
	SizeDouble(double w, double h);
	double getWidth();
	void setWidth(double value);
	double getHeight();
	void setHeight(double value);
	void toJS(nbind::cbOutput output);
};

class Color {
  private:
	double r;
	double g;
	double b;
	double a;

  public:
	Color(const Color &other);
	Color(double r, double g, double b, double a);
	double getR();
	void setR(double value);
	double getG();
	void setG(double value);
	double getB();
	void setB(double value);
	double getA();
	void setA(double value);
	void toJS(nbind::cbOutput output);
};

// UIArea

class DrawStrokeParams {
  private:
	uiDrawStrokeParams *sp;

  public:
	DrawStrokeParams();
	int getCap();
	int getJoin();
	double getThickness();
	double getMiterLimit();
	std::vector<double> getDashes();
	int getNumDashes();
	double getDashPhase();
	void setCap(int value);
	void setJoin(int value);
	void setThickness(double value);
	void setMiterLimit(double value);
	void setDashes(std::vector<double> value);
	void setNumDashes(int value);
	void setDashPhase(double value);
	uiDrawStrokeParams *toStruct();
	// void toJS(nbind::cbOutput output);
};
class UiDrawMatrix {
  private:
	uiDrawMatrix *m;

  public:
	UiDrawMatrix();
	uiDrawMatrix *getStruct();
	double getM11();
	double getM12();
	double getM21();
	double getM22();
	double getM31();
	double getM32();
	void setM11(double value);
	void setM12(double value);
	void setM21(double value);
	void setM22(double value);
	void setM31(double value);
	void setM32(double value);
	void setIdentity();
	void translate(double x, double y);
	void scale(double xCenter, double yCenter, double x, double y);
	void rotate(double x, double y, double amount);
	void skew(double x, double y, double xamount, double yamount);
	void multiply(UiDrawMatrix *src);
	int invertible();
	int invert();
	PointDouble transformPoint();
	SizeDouble transformSize();
};

class BrushGradientStop {
  private:
	double p;
	Color c;

  public:
	BrushGradientStop(double pos, Color color);
	Color getColor();
	void setColor(Color value);
	double getPos();
	void setPos(double value);
	void toJS(nbind::cbOutput output);
};

class DrawBrush {
  private:
	uiDrawBrush *b;

  public:
	DrawBrush();
	Color getColor();
	void setColor(Color value);
	Point getStart();
	void setStart(Point value);
	Point getEnd();
	void setEnd(Point value);
	int getType();
	void setType(int value);
	std::vector<BrushGradientStop> getStops();
	void setStops(std::vector<BrushGradientStop> value);
	uiDrawBrush *toStruct();
};

class UiAreaMouseEvent {
  private:
	uiAreaMouseEvent *e;

  public:
	UiAreaMouseEvent(uiAreaMouseEvent *event);
	double getX();
	double getY();
	double getAreaWidth();
	double getAreaHeight();
	int getDown();
	int getUp();
	int getCount();
	int getModifiers();
	unsigned int getHeld1To64();
};

class UiAreaKeyEvent {
  private:
	uiAreaKeyEvent *e;

  public:
	UiAreaKeyEvent(uiAreaKeyEvent *event);
	char *getKey();
	int getExtKey();
	int getModifier();
	int getModifiers();
	int getUp();
};

class UiDrawPath {
  private:
	uiDrawPath *handle;

  public:
	uiDrawPath *getHandle();
	UiDrawPath(int fillMode);
	void freePath();
	void newFigure(double x, double y);
	void newFigureWithArc(double xCenter, double yCenter, double radius,
						  double startAngle, double sweep, int negative);
	void lineTo(double x, double y);
	void arcTo(double xCenter, double yCenter, double radius, double startAngle,
			   double sweep, int negative);
	void bezierTo(double c1x, double c1y, double c2x, double c2y, double endX,
				  double endY);
	void closeFigure();
	void addRectangle(double x, double y, double width, double height);
	void end();
};

class DrawTextFontMetrics {
  private:
	uiDrawTextFontMetrics *m;

  public:
	DrawTextFontMetrics(uiDrawTextFontMetrics *metrics);
	double getAscent();
	double getDescent();
	double getLeading();
	double getUnderlinePos();
	double getUnderlineThickness();
};

class DrawTextFontDescriptor {
  private:
	uiDrawTextFontDescriptor *d;

  public:
	DrawTextFontDescriptor(uiDrawTextFontDescriptor *descr);
	const char *getFamily();
	double getSize();
	int getWeight();
	int getItalic();
	int getStretch();
};

class DrawTextFont {
  private:
	uiDrawTextFont *handle;

  public:
	DrawTextFont();
	DrawTextFont(uiDrawTextFont *h);

	uiDrawTextFont *getHandle();
	void free();
	DrawTextFontDescriptor *describe();
	DrawTextFontMetrics *getMetrics();

	static std::vector<char *> listFontFamilies();
	void loadClosestFont(const char *family, double size, int weight,
						 int italic, int stretch);
};

class DrawTextLayout {
  private:
	uiDrawTextLayout *handle;
	double w;

  public:
	DrawTextLayout(const char *text, DrawTextFont *defaultFont, double width);
	void free();
	void setWidth(double value);
	double getWidth();
	SizeDouble getExtents();
	uiDrawTextLayout *getHandle();
	void setColor(int startChar, int endChar, Color color);
};

class UiDrawContext {
  private:
	uiDrawContext *c;

  public:
	UiDrawContext(uiDrawContext *ctx);
	void stroke(UiDrawPath *path, DrawBrush *b, DrawStrokeParams *p);
	void fill(UiDrawPath *path, DrawBrush *b);
	void transform(UiDrawMatrix *m);
	void clip(UiDrawPath *path);
	void save();
	void restore();
	void text(double x, double y, DrawTextLayout *layout);
};

class UiAreaDrawParams {
  private:
	uiAreaDrawParams *p;

  public:
	UiAreaDrawParams(uiAreaDrawParams *params);
	UiDrawContext *getContext();
	double getAreaWidth();
	double getAreaHeight();
	double getClipX();
	double getClipY();
	double getClipWidth();
	double getClipHeight();
};

// TODO - document
class UiArea : public UiControl {
  public:
	// Workaround for nbind bug solved in 0.3
	UiArea(int dummy);

	UiArea(nbind::cbFunction &drawCb, nbind::cbFunction &mouseEventCb,
		   nbind::cbFunction &mouseCrossedCb, nbind::cbFunction &dragBrokenCb,
		   nbind::cbFunction &keyEventCb);
	UiArea(nbind::cbFunction &drawCb, nbind::cbFunction &mouseEventCb,
		   nbind::cbFunction &mouseCrossedCb, nbind::cbFunction &dragBrokenCb,
		   nbind::cbFunction &keyEventCb, int width, int height);
	void setSize(int width, int height);
	void queueRedrawAll();
	void scrollTo(double x, double y, double width, double height);
	DEFINE_CONTROL_METHODS()
};

extern std::map<uiArea *, UiArea *> areasMap;

typedef struct UiAreaHandler {
	void (*Draw)(UiAreaHandler *self, uiArea *area, uiAreaDrawParams *params);
	void (*MouseEvent)(UiAreaHandler *self, uiArea *area,
					   uiAreaMouseEvent *event);
	void (*MouseCrossed)(UiAreaHandler *self, uiArea *area, int left);
	void (*DragBroken)(UiAreaHandler *self, uiArea *area);
	int (*KeyEvent)(UiAreaHandler *self, uiArea *area, uiAreaKeyEvent *event);

	nbind::cbFunction *draw;
	nbind::cbFunction *mouseEvent;
	nbind::cbFunction *mouseCrossed;
	nbind::cbFunction *dragBroken;
	nbind::cbFunction *keyEvent;
} UiAreaHandler;

struct UiAreaHandlerFactory {
	static UiAreaHandler *build(nbind::cbFunction &draw,
								nbind::cbFunction &mouseEvent,
								nbind::cbFunction &mouseCrossed,
								nbind::cbFunction &dragBroken,
								nbind::cbFunction &keyEvent);
};

// This is included at end of file
// to minimize conflicts with existing
// symbols from other headers.
#include "nbind/nbind.h"

#endif
