#include "qr_code_texture_rect.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

QRCodeTextureRect::QRCodeTextureRect() {
    this->data = "";
    this->border_size = 1;
    this->fg_color = Color(0.0, 0.0, 0.0, 1.0);
    this->bg_color = Color(1.0, 1.0, 1.0, 1.0);
    this->set_expand_mode(ExpandMode::EXPAND_IGNORE_SIZE);
    this->set_stretch_mode(StretchMode::STRETCH_KEEP_ASPECT_CENTERED);
    this->set_texture_filter(TextureFilter::TEXTURE_FILTER_NEAREST);
};

QRCodeTextureRect::~QRCodeTextureRect() = default;

void QRCodeTextureRect::_ready() {
    UtilityFunctions::print("ready");
}

void QRCodeTextureRect::set_data(String p_data) {
    this->data = std::move(p_data);

    this->set_texture(generate_image_texture(generate_qr_code(this->data)));
}

String QRCodeTextureRect::get_data() {
    return this->data;
}

void QRCodeTextureRect::set_border_size(int32_t p_border_size) {
    this->border_size = p_border_size;

    this->set_texture(generate_image_texture(generate_qr_code(this->data)));
}

int32_t QRCodeTextureRect::get_border_size() {
    return this->border_size;
}

void QRCodeTextureRect::set_fg_color(godot::Color p_fg_color) {
    this->fg_color = p_fg_color;

    this->set_texture(generate_image_texture(generate_qr_code(this->data)));
}

Color QRCodeTextureRect::get_fg_color() {
    return this->fg_color;
}

void QRCodeTextureRect::set_bg_color(godot::Color p_bg_color) {
    this->bg_color = p_bg_color;

    this->set_texture(generate_image_texture(generate_qr_code(this->data)));
}

Color QRCodeTextureRect::get_bg_color() {
    return this->bg_color;
}

void QRCodeTextureRect::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_data", "data"), &QRCodeTextureRect::set_data);
    ClassDB::bind_method(D_METHOD("get_data"), &QRCodeTextureRect::get_data);
    ClassDB::add_property("QRCodeTextureRect", PropertyInfo(Variant::STRING, "data"), "set_data", "get_data");

    ClassDB::add_property_group("QRCodeTextureRect", "Appearance", "");
    ClassDB::bind_method(D_METHOD("set_border_size", "border_size"), &QRCodeTextureRect::set_border_size);
    ClassDB::bind_method(D_METHOD("get_border_size"), &QRCodeTextureRect::get_border_size);
    ClassDB::add_property("QRCodeTextureRect", PropertyInfo(Variant::INT, "border_size"), "set_border_size", "get_border_size");
    ClassDB::bind_method(D_METHOD("set_fg_color", "fg_color"), &QRCodeTextureRect::set_fg_color);
    ClassDB::bind_method(D_METHOD("get_fg_color"), &QRCodeTextureRect::get_fg_color);
    ClassDB::add_property("QRCodeTextureRect", PropertyInfo(Variant::COLOR, "fg_color"), "set_fg_color", "get_fg_color");
    ClassDB::bind_method(D_METHOD("set_bg_color", "bg_color"), &QRCodeTextureRect::set_bg_color);
    ClassDB::bind_method(D_METHOD("get_bg_color"), &QRCodeTextureRect::get_bg_color);
    ClassDB::add_property("QRCodeTextureRect", PropertyInfo(Variant::COLOR, "bg_color"), "set_bg_color", "get_bg_color");
}

QrCode QRCodeTextureRect::generate_qr_code(const String& p_data) {
    const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;
    const QrCode qr_code = QrCode::encodeText(p_data.ascii(), errCorLvl);
    return qr_code;
}

Ref<ImageTexture> QRCodeTextureRect::generate_image_texture(const qrcodegen::QrCode &qr_code) {
    Ref<Image> image = Image::create(qr_code.getSize() + this->border_size * 2, qr_code.getSize() + this->border_size * 2, false, Image::FORMAT_RGB8);
    image->fill(this->bg_color);

    for (int row = 0; row < qr_code.getSize(); row++) {
        for (int col = 0; col < qr_code.getSize(); col++) {
            Color color;
            if (qr_code.getModule(col, row)) {
                color = this->fg_color;
            } else {
                color = this->bg_color;
            }
            image->set_pixel(row + this->border_size, col + this->border_size, color);
        }
    }
    return ImageTexture::create_from_image(image);
}
