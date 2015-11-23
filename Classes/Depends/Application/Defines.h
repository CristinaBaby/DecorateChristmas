
#ifndef _Defines_h
#define _Defines_h


#define MY_SCENE(__TYPE__) \
static Scene* scene() \
{ \
Scene *scene = Scene::create();\
__TYPE__ *layer = __TYPE__::create();\
scene->addChild(layer);\
return scene;\
}

#endif
