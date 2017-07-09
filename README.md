### Design considerations

  * Should cover typical 3D printers, smaller CNC machines or laser cutters.
    * Of course, not every possible configuration can be supported with a
      limited connextor with fixed pins but that is explicitly a non-goal.
      It is encouraged to provide additional features via screw terminals.
  * Interoperability: Provides a standardized output to allow easy exchange of
    controller boards and allow independent competition in the controller
    world all providing a standard connector.
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

|Pos|Connection            | TOP | BTM |  Connection | Remarks
|---|---------------------:|:---:|:---:|:------------|---------------
| 1 | E-Stop Sw #1 |  1  |  2  | GND         | Emergency Stop Normally Closed, 10-20mA current loop.
| 2 |          GND |  3  |  4  | GND
| 3 |not connected |  5  |  6  | 5V-out      | -> 5V, max 1A out (for sensors)
| 4 |     POWER-IN |  7  |  8  | POWER-IN    | <- Power in; 12 or 24V. Up to 18A
| 5 |     POWER-IN |  9  | 10  | POWER-IN
| 6 |     POWER-IN | 11  | 12  | POWER-IN
| 7 |        PWM-1 | 13  | 14  | PWM-1       | 4 pins: 12A high side switch
| 8 |        PWM-1 | 15  | 16  | PWM-1
| 9 |        PWM-2 | 17  | 18  | PWM-2       | 4 pins: 12A high side switch
|10 |        PWM-2 | 19  | 20  | PWM-2
|11 |        PWM-3 | 21  | 22  | PWM-4       | two 3A low side switches
|12 |     Motor1+A | 23  | 24  | Motor1-A
|13 |     Motor1+B | 25  | 26  | Motor1-B
|14 |     Motor2+A | 27  | 28  | Motor2-A
|15 |     Motor2+B | 29  | 30  | Motor2-B
|16 |     Motor3+A | 31  | 32  | Motor3-A
|17 |     Motor3+B | 33  | 34  | Motor3-B
|18 |     Motor4+A | 35  | 36  | Motor4-A
|19 |     Motor4+B | 37  | 38  | Motor4-B
|20 |          GND | 39  | 40  | GND
|21 |      SW-NC-1 | 41  | 42  | SW-NC-2     |  end switches to GND,…
|22 |      SW-NC-3 | 43  | 44  | SW-NC-4     |  …Normally Closed,…
|23 |      SW-NC-5 | 45  | 46  | SW-NC-6     |   …Current Loop 10-20mA
|24 |   Analog-IN1 | 47  | 48  | Analog-IN2  |  Analog inputs. TBD: range
|25 |          GND | 49  | 50  | E-Stop Sw #2  | [---- END 25 Pos configuration ----]
|26 |      SW-NC-7 | 51  | 52  | SW-NC-8     | similar to SW-NC-1 to SW-NC-6
|27 |          TX+ | 53  | 54  | TX-         | RS485/422 TX. Open if not supported.
|28 |          RX+ | 55  | 56  | RX-         | RS485/422 RX. Open if not supported.
|29 |          GND | 57  | 58  | GND
|30 |     Motor5+A | 59  | 60  | Motor5-A
|31 |     Motor5+B | 61  | 62  | Motor5-B    | [---- END 31 Pos configuration ----]
|32 |     Motor6+A | 63  | 64  | Motor6-A
|33 |     Motor6+B | 65  | 66  | Motor6-B
|34 |     Motor7+A | 67  | 68  | Motor7-A
|35 |     Motor7+B | 69  | 70  | Motor7-B
|36 |         GND  | 71  | 72  | GND         | [---- END 36 Pos configuration ----]
