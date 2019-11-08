# integrated\_nRF5\_SDK\_15.3.0\_59ac345
nRF5\_SDK\_15.3.0\_59ac345 examples with obvious integrated. Currently, only the PCA10040 development kit with SoftDevice S132 and an ARM GCC toolchain are supported. Note that the following guide was developed using a macOS environment. To test the non-Obvious functionality of the examples, please refer to the [Nordic Semiconductor Infocentre](https://infocenter.nordicsemi.com/topic/com.nordic.infocenter.sdk5.v15.3.0/examples_ble_peripheral.html).

## Step-By-Step Integration Guide
1. Create a new Obvious portal on [our website](https://portal.obvious.xyz/create).
2. Once logged in, create a new product by clicking "Add" in the top-right corner of the portal's "Products" tab. 
  * For these examples, name your product "Example Product"
  * The feature region size should be 4096.
3. Click on your product, and create a new feature by clicking "Add" in the top-right corner of the product's "Features" tab.
  * For these examples, name your feature "Feature LED 4". If you wish to evaluate the ble\_app\_uart example, name your feature "Feature UART".
  * Using the drop-down list, select "Purchasable" as the option for how the feature is to be delivered.
  * Toggle the "Feature Status" button to the "on" position.
4. Add the feature to your product's catalog.
  * Navigate to the portal's "Sales" tab, and select the "Catalog" option.
  * Select your product, and then click the "Add" button in the top-right corner of the page.
  * Select "Individual" as the type of catalog item from the first drop-down menu, and select the name of your feature from the second drop-down menu.
  * Give your catalog entry a name, description, SKU, and a price. Enter image and thumbnail URLs if you wish. Then, click the "Add Individual Entry" button at the bottom of the form.
5. Build and download the embedded library.
  * Navigate to your product's "Firmware" tab.
  * Select the "Library" option, and click "Create" in the top-right corner of the page.
  * Select SoftDevice S132, and choose version 6.1.1 from the drop-down list.
  * Select NRF52832\_XXAA as your chip.
  * Set Ocelot Flash Start to 0x7A000, and Ocelot Reset Safe Ram Start to 0x2000FFE0
  * Click "Generate SDK library".
  * Once the build finishes, click "Download" on the card displaying your build's details and extract the .zip file to a location of your choosing.
6. Navigate to the portal's "Tools" tab, select the "Product File Generators" option, and click "Embedded" on the right side of the page to download a file that contains information concerning your products and features called "ocelot\_feature.h".
7. Copy the files "ocelot.h" and "libocelot.ld" from the extracted library folder as well as "ocelot\_feature.h" to $(INSTALL\_ROOT)/ocelot/include/
8. Copy "libocelot.a" from the library folder to $(INSTALL\_ROOT)/ocelot/lib/
9. Navigate to the Makefile of the example you wish to evaluate. For example, if you would like to evaluate the ble\_app\_blinky example, navigate to $(INSTALL\_ROOT)/obvious\_examples/ble\_peripheral/ble\_app\_blinky/pca10040/s132/armgcc
10. Set the GNU\_INSTALL\_ROOT environment variable to /usr/local/gcc-arm-none-eabi-7-2018-q2-update/bin/ and ensure that ARM GCC 7-2018-q2-update is indeed located in the aforementioned location.
11. Build the example by entering the ```make``` command.
12. Program the example onto your development kit by entering ```make erase```, ```make flash_softdevice```, and then ```make flash```
13. Back in the portal, select your product and navigate to the "Keys" page. Then, make note of your 16-byte product key. This key must be flashed onto your development board at address 0x7B000. One option is to copy the product key into a .bin file and use the J-Link Commander utility's loadbin command to load the key to the aforementioned address. At this point, the example can be tested with the Obvious Discover app!
14. In the Obvious Discover app, select your device from the scan menu. You may wish to filter the list by tapping the three dots on the top-right side of the screen.
15. Once your device has been selected, it will be provisioned automatically, and a feature update will occur. Notice that LED 4 on the development kit is not on. If you are evaluating the ble\_app\_uart example, notice that messages will be printed to the terminal backwards.
16. Navigate to the app's checkout tab, select your feature, and tap "Checkout". To purchase the feature, use the test Visa number 4242424242424242 with expiry 10/30 and CVV 123.
17. Once the purchase is complete, notice that LED 4 on the development board is turned on. If you are evaluating the ble\_app\_uart example, notice that messages are now printed to the terminal properly.
18. Return to the device menu and experiment with toggling the feature that was just purchased by tapping the button at the bottom of the card titled with the feature's name. In this way, the purchased feature can easily be activated and deactivated on the device!

  
