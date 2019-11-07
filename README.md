# integrated\_nRF5\_SDK\_15.3.0\_59ac345
nRF5\_SDK\_15.3.0\_59ac345 examples with obvious integrated. Note that the following guide was developed using a macOS environment.

## Step-By-Step Integration Guide
1. Create a new Obvious portal on [our website](https://portal.obvious.xyz/create).
2. Once logged in, create a new product by clicking "Add" in the top-right corner of the portal's "Products" tab. 
  * For these examples, name your product "Example Product"
  * The feature region size should be 4096.
3. Click on your product, and create a new feature by clicking "Add" in the top-right corner of the product's "Features" tab.
  * For these examples, name your feature "Feature Blink LED 4".
  * Using the drop-down list, select "Provision" as the option for how the feature is to be delivered.
  * Toggle the "Feature Status" button to the "on" position.
4. Build and download the embedded library.
  * Navigate to your product's "Firmware" tab.
  * Select the "Library" option, and click "Create" in the top-right corner of the page.
  * Select SoftDevice S132, and choose version 6.1.1 from the drop-down list.
  * Select NRF52832\_XXAA as your chip.
  * Set Ocelot Flash Start to 0x7A000, and Ocelot Reset Safe Ram Start to 0x2000FFE0
  * Click "Generate SDK library".
  * Once the build finishes, click "Download" on the card displaying your build's details and extract the .zip file to a location of your choosing.
5. Navigate to the portal's "Tools" tab, select the "Product File Generators" option, and click "Embedded" on the right side of the page to download a file that contains information concerning your products and features called "ocelot\_feature.h".
6. Copy the files "ocelot.h" and "libocelot.ld" from the extracted library folder as well as "ocelot\_feature.h" to $(INSTALL\_ROOT)/ocelot/include/
7. Copy "libocelot.a" from the library folder to $(INSTALL\_ROOT)/ocelot/lib/
8. Navigate to the Makefile of the example you wish to evaluate. For example, if you would like to evaluate the ble\_app\_blinky example, navigate to $(INSTALL\_ROOT)/obvious\_examples/ble\_peripheral/ble\_app\_blinky/pca10040/s132/armgcc
9. Set the GNU\_INSTALL\_ROOT environment variable to /usr/local/gcc-arm-none-eabi-7-2018-q2-update/bin/ and ensure that ARM GCC 7-2018-q2-update is indeed located in the aforementioned location.
10. Build the example by entering the ```make``` command.
11. Program the example onto your development kit by entering ```make erase```, ```make flash_softdevice```, and then ```make flash```
  
