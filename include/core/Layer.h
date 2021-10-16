#ifndef CORE_LAYER_H
#define CORE_LAYER_H

#include "Essentials.h"
#include "LayerLinked.h"
#include "IDrawable.h"
#include "Instantiable.h"
#include "Object.h"

namespace core {

class Layer : public Object, public IDrawable {
public:
    explicit Layer(const string& name);

    /** Move constructor */
    Layer(Layer&& other) = default;

    /** Copying is not allowed */
    Layer(const Layer& other) = delete;

    static bool LayerExist(const string& name);
    static Layer* CreateNewLayer(const string& name);
    static Layer* Get(const string& name);

    template<typename T>
    void Link(T& obj);

    template<typename T>
    void Unlink(T& obj);

    template<typename T>
    bool IsLinked(T& obj);

    void Draw() override;
    void SetProjectionMatrix(Matrix4& mtx) override;
    void SetTransformMatrix(Matrix4& mtx) override;

protected:
    friend class Camera;

    template<typename T>
    vector<T*>& GetContainerForType();

    std::vector<Entity*> entities;
    std::vector<Camera*> cameras;
    std::vector<Light*>  lights;

private:

    template<typename T>
    void assertSupportedType();


    static std::vector<unique<Layer>> layers;

};

} // namespace core

#include "Layer.tpp"

#endif //CORE_LAYER_H
