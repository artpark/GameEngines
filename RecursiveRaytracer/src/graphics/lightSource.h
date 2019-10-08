#ifndef LightSource_h
#define LightSource_h

class LightSource {
    public:
        Vec3 center;

        LightSource(Vec3 c) : center(c) {}
};

#endif