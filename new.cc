
#include QByteArray wetext::sendImage(QPixmap pix, int page, int effect, int speed, int duration)
{
    QString pagestr;

    if(page/10 < 1) // Append "0" to first byte if page number is smaller than 10
    {
        pagestr.append("0");
        pagestr.append(QString::number(page));
    }
    else
    {
        pagestr.append(QString::number(page));
    }

    QImage img = pix.toImage();

    if(img.format() != QImage::Format_Indexed8)
    {
        img = img.convertToFormat(QImage::Format_Indexed8);
    }

     /* Set image pixels to RGB values */

    QByteArray red_ar;
    QByteArray green_ar;
    QByteArray blue_ar;
    QByteArray image_data;

    for(int y_=0; y_ < img.height(); y_++)
    {
        for(int x=0; x < img.width(); x+=8)
        {
            char red = 0;
            char green = 0;
            char blue = 0;

            for(int offs=0; offs < 8; offs++)
            {
                if(qRed(img.pixel(x + offs, y_))   > RED_SEPERATION_VALUE  )  red   |= (1 << offs);
                if(qGreen(img.pixel(x + offs, y_)) > GREEN_SEPERATION_VALUE ) green |= (1 << offs);
                if(qBlue(img.pixel(x + offs, y_))  > BLUE_SEPERATION_VALUE )  blue  |= (1 << offs);
            }

            red_ar.append(red);
            green_ar.append(green);
            blue_ar.append(blue);
        }
    }

    image_data.append(red_ar);
    image_data.append(green_ar);
    image_data.append(blue_ar);

    QByteArray data;

    data.append(TCP_PRELUDE);                       // 1 Intro 0x00
    data.append(TCP_PRELUDE);                       // 2 Intro 0x00
    data.append(TCP_PRELUDE);                       // 3 Intro 0x00
    data.append(m_serial_address);                  // 4 Display ID
    data.append(SIMPLE_GRAPHIC);                    // 5 0x02

    data.append(TCP_STX);                           // 6 0x02
    data.append('W');                               // 7 Write operation
    data.append(pagestr);                           // 8-9
    data.append(effect);                            // 10
    data.append(speed);                             // 11
    data.append(duration);                          // 12
    data.append((char)0x00);                        // 13 RESERVED
    data.append(image_data);                        // 14 ... n Image Data as QByteArray
    data.append(TCP_FRAME_END);                     // n+1

    return data;
}
