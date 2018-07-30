// Credit for the Mac dialog box code goes to https://github.com/aaronmjacobs
#include <CoreFoundation/CoreFoundation.h>

// Icons to decorate the dialog message box.
// Use `Icon::None` for no icon decoration.
struct Icon
{
    enum Enum
    {
        None,
        Information,
        Warning,
        Error
    };
};

// Buttons present in the dialog message box.
// The clicked button is returned by `showMessageBox()`.
// These can be combined as flags in the `buttons` parameter.
struct Button
{
    enum Enum
    {
        Ok     = 1 << 0, // Has an OK/accept button
        Cancel = 1 << 1  // Has a cancel button
    };
};

Button::Enum showMessageBox(Icon::Enum icon, unsigned int buttons, const char * title, const char * message)
{
    //
    // Similar question pertaining `CFUserNotificationDisplayAlert()` and iOS:
    //   http://stackoverflow.com/questions/2199642/display-cfusernotificationdisplayalert-on-iphone-lock-screen
    //

    // Provide defaults in case of null:
    if (title   == nullptr) { title   = "(null)"; }
    if (message == nullptr) { message = "???";    }

    CFOptionFlags cfAlertIcon;
    switch (icon)
    {
    case Icon::Information :
        cfAlertIcon = kCFUserNotificationNoteAlertLevel;
        break;

    case Icon::Warning :
        cfAlertIcon = kCFUserNotificationCautionAlertLevel;
        break;

    case Icon::Error :
        cfAlertIcon = kCFUserNotificationStopAlertLevel;
        break;

    default : // Icon::None
        cfAlertIcon = kCFUserNotificationPlainAlertLevel;
        break;
    } // switch (icon)

    // Convert button flags to CF strings:
    CFStringRef cfStrDefaultButton   = nullptr;
    CFStringRef cfStrAlternateButton = nullptr;
    bool isDefaultBtnCancel = false;

    if ((buttons & Button::Ok) && (buttons & Button::Cancel))
    {
        cfStrDefaultButton   = CFSTR("OK");
        cfStrAlternateButton = CFSTR("Cancel");
    }
    else if (buttons & Button::Ok)
    {
        cfStrDefaultButton = CFSTR("OK");
    }
    else if (buttons & Button::Cancel)
    {
        cfStrDefaultButton = CFSTR("Cancel");
        isDefaultBtnCancel = true;
    }
    else
    {
        // Bad flags, display the OK button anyway.
        cfStrDefaultButton = CFSTR("OK");
    }

    CFStringRef cfStrHeader  = CFStringCreateWithCString(kCFAllocatorDefault, title,   kCFStringEncodingUTF8);
    CFStringRef cfStrMessage = CFStringCreateWithCString(kCFAllocatorDefault, message, kCFStringEncodingUTF8);

    // Launch the message box, blocking the current thread
    // until the user click a button or closes the dialog.
    CFOptionFlags result;
    CFUserNotificationDisplayAlert(
        0,                    // No timeout
        cfAlertIcon,          // Icon of the message box
        nullptr,              // Icon URL if loading from web
        nullptr,              // Second URL ???
        nullptr,              // Localized strings
        cfStrHeader,          // Header text
        cfStrMessage,         // Message text
        cfStrDefaultButton,   // Default button
        cfStrAlternateButton, // Second button
        nullptr,              // Third button, null -> no other button
        &result               // Response flags
    );

    CFRelease(cfStrHeader);
    CFRelease(cfStrMessage);

    if (result == kCFUserNotificationDefaultResponse)
    {
        return isDefaultBtnCancel ? Button::Cancel : Button::Ok;
    }

    // kCFUserNotificationAlternateResponse
    return Button::Cancel;
}

// Storm code starts below:
#include <SErr.inl>

void SErrDisplayError(const char *inText, const char *inTitle)
{
	showMessageBox(Icon::Error, Button::Ok, inTitle, inText);
}
