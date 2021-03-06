#include "main.hpp"

#include "exception/OptionsException.hpp"
#include "options/parse_options.hpp"
#include "options/get_help_string.hpp"
#include "scene/make_scene.hpp"
#include "material/make_material.hpp"
#include "texture/make_texture.hpp"
#include "object/make_object.hpp"
#include "camera/make_camera.hpp"
#include "image/make_output_image.hpp"
#include "tracer/trace_scene.hpp"

auto parse_options(int argc, char **argv) {
    try {
        return Myrt::Options::try_parse_options(argc, argv);
    } catch (Myrt::Exception::OptionsHelpException& ex) {
        std::cerr << Myrt::Options::get_help_string() << std::endl;
        std::exit(0);
    } catch (Myrt::Exception::OptionsException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::cerr << Myrt::Options::get_help_string() << std::endl;
        std::exit(1);
    }
}

auto prepare_test_scene_one_sphere(float aspect) {
    using Myrt::Scene::make_scene;
    auto scene = make_scene();

    using Myrt::Object::make_object;
    using Myrt::Object::Sphere;
    auto object = make_object<Sphere>(Vec4(0.f, 0.f, 0.f), .5f);

    using Myrt::Texture::make_texture;
    using Myrt::Texture::Constant;
    using Myrt::Texture::Checker;
    auto textureRed = make_texture<Constant>(Color(1.f, 1.f, 1.f));
    auto textureBlack = make_texture<Constant>(Color(0.f, 0.f, 0.f));
    auto textureChecker = make_texture<Checker>(textureRed, textureBlack, 8, 4);

    using Myrt::Material::make_material;
    using Myrt::Material::Lambertian;
    using Myrt::Material::Metal;
    using Myrt::Material::Dielectric;
    auto material = make_material<Lambertian>(textureChecker);
    object->setMaterial(material);
    scene->addObject(object);

    using Myrt::Camera::make_camera;
    auto pCamera = make_camera<Myrt::Camera::SimpleCamera>(
            Vec4(0.f, 0.f, -3.f), Vec4(0.f, 0.f, 0.f), Vec4(0.f, 1.f, 0.f),
            25.f, aspect);
    scene->setCamera(pCamera);

    return scene;
}

auto prepare_test_scene(float aspect) {
    using Myrt::Scene::make_scene;
    auto scene = make_scene();

    using Myrt::Object::make_object;
    using Myrt::Object::Sphere;
    auto object1 = make_object<Sphere>(Vec4(0.f, 0.f, 0.f), .5f);
    auto object2 = make_object<Sphere>(Vec4(0.f, -100.5f, 0.f), 100.f);
    auto object3 = make_object<Sphere>(Vec4(1.f, 0.f, 0.f), .5f);
    auto object4 = make_object<Sphere>(Vec4(-1.f, 0.f, 0.f), .5f);

    using Myrt::Texture::make_texture;
    using Myrt::Texture::Constant;
    using Myrt::Texture::Checker;
    auto texture1 = make_texture<Constant>(Color(.1f, .2f, .5f));
    auto texture2 = make_texture<Constant>(Color(.8f, .8f, .0f));
    auto texture3 = make_texture<Constant>(Color(.8f, .5f, .2f));
    auto texture4 = make_texture<Constant>(Color(.8f, .8f, .8f));

    auto textureRed = make_texture<Constant>(Color(1.f, 1.f, 1.f));
    auto textureBlack = make_texture<Constant>(Color(0.f, 0.f, 0.f));
    auto textureChecker = make_texture<Checker>(textureRed, textureBlack, 4, 4);

    using Myrt::Material::make_material;
    using Myrt::Material::Lambertian;
    using Myrt::Material::Metal;
    using Myrt::Material::Dielectric;
    auto material1 = make_material<Lambertian>(textureChecker);
    auto material2 = make_material<Lambertian>(texture2);
    auto material3 = make_material<Metal>(texture3);
    auto material4 = make_material<Metal>(texture4, 1.f);

    object1->setMaterial(material1);
    object2->setMaterial(material2);
    object3->setMaterial(material3);
    object4->setMaterial(material4);

    scene->addObject(object1);
    scene->addObject(object2);
    scene->addObject(object3);
    scene->addObject(object4);

    using Myrt::Camera::make_camera;
    using Myrt::Camera::SimpleCamera;
    using Myrt::Camera::LensCamera;
    auto pCamera = make_camera<SimpleCamera>(
            Vec4(-1.15f, 0.15f, 3.f), Vec4(-.15f, 0.f, 0.f), Vec4(0.f, 1.f, 0.f),
            30.f, aspect);
    scene->setCamera(pCamera);

    return scene;
}

int main(int argc, char **argv) {
    using Myrt::Image::make_output_image;
    using Myrt::Tracer::trace_scene;

    auto options = parse_options(argc, argv);
    auto image = make_output_image(options->getOutputImageOptions());
    auto scene = prepare_test_scene(image->getAspectRatio());
    trace_scene<Myrt::Tracer::SimpleTracer>(options->getTracerOptions(), scene, image);
    image->save();
}

