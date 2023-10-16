#ifndef QR_CODE_TEXTURE_RECT_HPP
#define QR_CODE_TEXTURE_RECT_HPP

#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/image_texture.hpp>

#include "qr_code_generator.hpp"

using qrcodegen::QrCode;

namespace godot {
    class QRCodeTextureRect : public TextureRect {
        GDCLASS(QRCodeTextureRect, TextureRect)

    private:
        String data;

        int32_t border_size;
        Color fg_color;
        Color bg_color;

        static QrCode generate_qr_code(const String& data);
        Ref<ImageTexture> generate_image_texture(const QrCode &qr_code);

    protected:
        static void _bind_methods();

    public:
        QRCodeTextureRect();
        ~QRCodeTextureRect();

        void _ready() override;

        void set_data(String data);
        String get_data();

        void set_border_size(int32_t border_size);
        int32_t get_border_size();
        void set_fg_color(Color fg_color);
        Color get_fg_color();
        void set_bg_color(Color bg_color);
        Color get_bg_color();
    };
}

#endif //QR_CODE_TEXTURE_RECT_HPP
