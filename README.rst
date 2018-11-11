======================
leberg-air-conditioner
======================

Arduino library for IR code building for Leberg air conditioner

Description
===========

Given parameters of an air conditioner state you can build IR code
and send it using `IRremote <https://github.com/z3t0/Arduino-IRremote>`_.

Usage
======================

.. code-block:: c++

    #include <IRremote.h>
    #include "LebergAirConditioner.h"

    unsigned short int code[IR_LENGTH];
    IRsend irsend;

    void switchPower(bool power) {
        build_code(code, power, ECO_OFF, MODE_COOL, SUPER_OFF, TEMP_23C, FAN_LOW, SWING_ON, 0);
        irsend.sendRaw(code, IR_LENGTH, 38);
    }

    // ...


For advanced usage see `examples <https://github.com/insolite/leberg-air-conditioner/tree/master/examples>`_.

Download
======================
`Latest release <https://github.com/insolite/leberg-air-conditioner/releases/latest>`_

Disclaimer
==========
This is an implementation of reverse-engineered remote for Leberg LBS-FRA10 model.
All features provided by original remote are supported, however the protocol isn't
investigated to the very end. Support for other models isn't guaranteed but feel free
to open an issue if you find something interesting.
