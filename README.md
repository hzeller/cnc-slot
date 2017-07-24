### Design considerations
  * Goal is to cover the _electrical_ connection to the machine
    (motors, switches, ...), and explicitly does not define the interfacing
    on the data side - USB, Ethernet, Wireless ? GCode or simple Sub-D25 stepper
    input ? LCD display and user interface or not ?
    This is part of the feature-set provided by the cardridge, but not part
    of the electrical connection to the actuators and switches of the machine.
  * Should cover typical 3D printers, smaller CNC machines or laser cutters.
    * Of course, not every possible configuration can be supported with a
      limited connextor with fixed pins but that is explicitly a non-goal. This
      is to define the basic functions that is needed for 98% of all devices.
      It is encouraged to provide additional features via screw terminals or
      the specified robust RS485 bus.
  * Interoperability: Provides a standardized output to allow easy exchange of
    controller boards and allow independent competition in the controller
    world all providing a standard connector. Competition can focus on
    software features, microstepping, motor current capability etc.
  * Within the same standard connector, there then can be distinguishing
    features of various controllers: provided current for motors, or if the
    two power PWMs can be used together as an H-Bridge.
  * Simplify wire harnesses. They are now fixed part of the printer all
    connecting to the card-edge connector. Easy to pre-fabricate with the
    right cable lengths. Less issues with confusing 'cable salads'.
  * Multiple configurations from minimal 3D printer with up to four steppers
    (with a 25 Pos card edge connector that is shorter than a 70mm PCB) to
    larger machines with specific requirements: Next level with 31 Pos
    features an additional motor and a noise resistant
    RS485 high speed serial bus to communicate with machine sub-components.
    36 pos level adds two more motors.
  * Enforce some safety features and electric recommendations directly in the
    specification that are not yet commonly seen in many controllers today:
     * The high power PWM outputs are only high-side switches to minimize
       dangerous heater-stuck-on failure scenarios.
     * Emergency Stop Switch is part of the specification. Contacts
       strategically placed so that card insertion issues or hot-unplugging
       trigger it.
     * Have all kinds of external switch inputs be current loops and
       normally closed for more resilience.

### Finger levels
The fingers on the card edge come in three lengths

  * most signals including GND: connect first, all the way to the edge
  * Power connect second.
  * Emergency stop switches connect third, most recessed fingers.

|Pos|Connection    | TOP | BTM |  Connection | Remarks
|---|-------------:|:---:|:---:|:------------|---------------
| 1 | E-Stop Sw #1 |  1  |  2  | GND         | Emergency Stop Normally Closed, 10-20mA current loop.
| 2 |          N/C |  3  |  4  | 5V-out      | -> 5V, max 1A out (for sensors)
| 3 |        PWM-1 |  5  |  6  | PWM-1       | 4 pins: 12A high side switch
| 4 |        PWM-1 |  7  |  8  | PWM-1       | (optional: push pull offering H-Bridge with PWM-2)
| 5 |        PWM-2 |  9  | 10  | PWM-2       | 4 pins: 12A high side switch
| 6 |        PWM-2 | 11  | 12  | PWM-2       | (optional: push pull offering H-Bridge with PWM-1)
| 7 |        PWM-3 | 13  | 14  | PWM-4       | two 3A low side switches
| 8 |     Motor1+A | 15  | 16  | Motor1-A
| 9 |     Motor1+B | 17  | 18  | Motor1-B
|10 |     Motor2+A | 19  | 20  | Motor2-A
|11 |     Motor2+B | 21  | 22  | Motor2-B
|12 |     Motor3+A | 23  | 24  | Motor3-A
|13 |     Motor3+B | 25  | 26  | Motor3-B
|14 |     Motor4+A | 27  | 28  | Motor4-A
|15 |     Motor4+B | 29  | 30  | Motor4-B
|16 |          GND | 31  | 32  | GND
|17 |      SW-NC-1 | 33  | 34  | SW-NC-2     |  end switches to GND,…
|18 |      SW-NC-3 | 35  | 36  | SW-NC-4     |  …Normally Closed,…
|19 |      SW-NC-5 | 37  | 38  | SW-NC-6     |  …Current Loop 10-20mA
|20 |          SDA | 39  | 40  | SCL         | I2C bus.
|21 |    TX-RS422+ | 41  | 42  | TX-RS422-   | RS422-TX. Open if not supported.
|22 |  RXTX-RS485+ | 43  | 44  | RXTX-RS485- | RS485 Bus and/or RS422-RX; Open if not supported.
|23 |          GND | 45  | 46  | GND
|24 |   Analog-IN1 | 47  | 48  | Analog-IN2  |  Analog inputs. TBD: range
|25 |          GND | 49  | 50  | E-Stop Sw #2| [---- END 25 Pos configuration ----]
|26 |      SW-NC-7 | 51  | 52  | SW-NC-8     | similar to SW-NC-1 to SW-NC-6
|27 |          N/C | 53  | 54  | N/C         | Not connected in Version #1 (CAN+/CAN- in future ?)
|28 |     Motor5+A | 55  | 56  | Motor5-A
|29 |     Motor5+B | 57  | 58  | Motor5-B
|30 |     Motor6+A | 59  | 60  | Motor6-A
|31 |     Motor6+B | 61  | 62  | Motor6-B    | [---- END 31 Pos configuration ----]
|32 |     Motor7+A | 63  | 64  | Motor7-A
|33 |     Motor7+B | 65  | 66  | Motor7-B
|34 |         GND  | 67  | 68  | GND
|35 |         GND  | 69  | 70  | GND
|36 |         GND  | 71  | 72  | GND         | [---- END 36 Pos configuration ----]

FAQ
 * why are the motors numbered Motor1, Motor2 and not X, Y, Z ?
 * Depending on the geometry of the machine, this can have different meanings.