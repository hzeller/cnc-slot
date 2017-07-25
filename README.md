# CNC Standard Slot connector
Goal is to define a standardized connection between typical small CNC machines
or 3D printers that allows to minimize the effort to cable everything.

Status quo is, that there are many boards out there that each provide their own
connectors for motors, endswitches and PWM, and wiring up any machine to a
motor controller board is a mess and requires careful labeling of wires (any
3D printer cabling at the controller board has been a mess that I have seen).
Replacing a board with some other board of another manufacturer requires
wiring in different places, possibly re-crimping cables etc.

This effort defines a card edge connector that should cover the typical
use-cases in these machines. The electrical connection is
  * a 0.1" pitch card edge connector on the controller board side (the "controller cartridge")
  * a PCB with card edge 'fingers' on the machine side. That board is the origin
    of all the wire harness for that particular machine.
Further definition for sizes of the controller cartridge cases, fan options etc.
have to be defined.

The goals are to cover typical use cases in these small machines:
   * Controls bipolar stepper motors up to 3-4A.
   * Provides 2 high power and 2 low power PWM outputs
   * Strongly suggests and requires a couple of safety features.
   * Has a fixed layout, so that a particular pin always is at the same
     place no matter the manufacturer of the controller cartridge.
   * Suggests a couple of serial busses that are more and more needed in
     modern devices.
   * Smallest 25 Pos configuration good for a typical 3D printer.

### Design considerations
(some grab-bag of loosely formulated goals)

  * Interoperability: Provides a standardized output to allow easy exchange of
    controller boards and allow independent competition in the controller
    world, all providing this standard connector. Competition can focus on
    software features, microstepping, motor current capability etc.; the standardized
    connector encourages the users experimenting with different solutions.
  * Goal is to cover the _electrical_ connection to the machine
    (motors, switches, ...), that will allow to have the complicated cable
    harness inside the machine terminate in one place with a specific interface.
  * Non Goals: Explicitly does not define the interfacing
    on the data side - USB, Ethernet, Wireless ? GCode or simple Sub-D25 stepper
    input ? LCD display and user interface or not ?
    This is part of the feature-set provided by the cartridge, but not part
    of the electrical connection to the actuators and switches of the machine.
  * Should cover typical 3D printers, smaller CNC machines or laser cutters.
    * Of course, not every possible configuration can be supported with a
      limited connector with fixed pins but that is explicitly a non-goal. This
      is to define the basic functions that is needed for 98% of all devices.
      It is encouraged to provide additional features via screw terminals or
      the specified robust RS485 bus.
  * Within the same standard connector, there then can be distinguishing
    features of various controllers: provided current for motors, or if the
    two power PWMs can be used together as an H-Bridge.
  * Simplify wire harnesses. They are now fixed part of the printer all
    connecting to the card-edge connector. Easy to pre-fabricate with the
    right cable lengths. Less issues with confusing 'cable salads'.
  * Multiple configurations from minimal 3D printer with up to four steppers
    (with a **25 Pos** card edge connector that is shorter than a 70mm PCB) to
    larger machines with specific requirements: Next level with **31 Pos**
    and **36 pos** level adding more motors.
  * Enforce some safety features and electric recommendations directly in the
    specification that are not yet commonly seen in many controllers today:
     * The high power PWM outputs are only high-side switches to minimize
       dangerous heater-stuck-on failure scenarios.
     * Emergency Stop Switch is part of the specification. Contacts
       strategically placed so that card insertion issues or hot-unplugging
       trigger it.
     * Have all kinds of external switch inputs be current loops and
       normally closed for more resilience.
  * For periphery: suggest busses that are proper in the noisy environment (RS422/485)
    instead of flaky I²C not well suited for an electrically noisy machine.
  * There are two analog inputs, and they define a particular input range in
    voltage.
    That means that adapter amplifiers need to be done on
    the machine side. This allows to adapt various inputs (e.g. Thermistors,
    PT100, ...) without assuming a particular analog interface.
  * (After initial inclusion of power connection, this is now removed as this
    might be handled differently per device)

### Finger levels
The fingers on the card edge come in two lengths

  * All signals including GND: connect first, all the way to the edge.
  * Emergency stop switches connect with recessed fingers.

All output pins can only switch on iff the two e-stop wires on pin 1 and 50
are connected with each other (this will be a current loop of 10mA or so).
The fact that the two pins are recessed and at opposite ends of the connector
will make sure that the outputs are switched off before the connector is being
disconnected completely. This prevents fried motor drivers and accidental shorts.
Even a brief interruption of the e-stop will require a reset from software.

N/C = Not Connected. Typically place holders for Version #1 of this spec.

|Pos|Connection    | BTM | TOP |  Connection | Remarks
|---|-------------:|:---:|:---:|:------------|---------------
| 1 | E-Stop-Sw#1  |  1  |  2  | GND         | Emergency Stop Normally Closed, 10-20mA current loop.
| 2 |          N/C |  3  |  4  | 5V-out      | -> 5V, max 1A out (for sensors)
| 3 |        PWM-1 |  5  |  6  | PWM-1       | 4 parallel pins: 12A high side switch
| 4 |        PWM-1 |  7  |  8  | PWM-1       | (optional: push pull offering H-Bridge with PWM-2)
| 5 |        PWM-2 |  9  | 10  | PWM-2       | 4 parallel pins: 12A high side switch
| 6 |        PWM-2 | 11  | 12  | PWM-2       | (optional: push pull offering H-Bridge with PWM-1)
| 7 |        PWM-3 | 13  | 14  | PWM-4       | two 3A low side switching PWM (maybe need more?)
| 8 |     Motor1+A | 15  | 16  | Motor1-A    | 4x Bipolar stepper motors.
| 9 |     Motor1+B | 17  | 18  | Motor1-B    | ...
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
|20 |    TX-RS422+ | 39  | 40  | TX-RS422-   | RS422-TX. N/C if not supported.
|21 |  RXTX-RS485+ | 41  | 42  | RXTX-RS485- | RS485 Bus and/or RS422-RX; N/C if not supported.
|22 |          GND | 43  | 44  | GND
|23 |          N/C | 45  | 46  | N/C         | Not connected in Version #1.
|24 |   Analog-IN1 | 47  | 48  | Analog-IN2  |  Analog inputs. TBD: range (0..2V?)
|25 |          GND | 49  | 50  | E-Stop-Sw#2 | **[---- END 25 Pos configuration ----]**
|26 |      SW-NC-7 | 51  | 52  | SW-NC-8     | similar to SW-NC-1 to SW-NC-6
|27 |          N/C | 53  | 54  | N/C         | N/C in Version #1 (future: CAN+/CAN- or I²C SDA/SCL ?)
|28 |     Motor5+A | 55  | 56  | Motor5-A
|29 |     Motor5+B | 57  | 58  | Motor5-B
|30 |     Motor6+A | 59  | 60  | Motor6-A
|31 |     Motor6+B | 61  | 62  | Motor6-B    | **[---- END 31 Pos configuration ----]**
|32 |     Motor7+A | 63  | 64  | Motor7-A    | Anyone needs more than 6 motors ?
|33 |     Motor7+B | 65  | 66  | Motor7-B
|34 |         N/C  | 67  | 68  | N/C         | TODO: what else we want ?
|35 |         N/C  | 69  | 70  | N/C
|36 |         GND  | 71  | 72  | GND         | **[---- END 36 Pos configuration ----]**

FAQ
 * Q: why are the motors numbered Motor1, Motor2 and not X, Y, Z ?
 * A: Depending on the geometry of the machine, this can have different meanings.