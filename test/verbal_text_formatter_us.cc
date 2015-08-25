#include <regex>

#include "test.h"
#include "valhalla/baldr/verbal_text_formatter.h"
#include "valhalla/baldr/verbal_text_formatter_us.h"

using namespace std;
using namespace valhalla::baldr;

namespace {

// Sub class to test protected methods
class VerbalTextFormatterUsTest : public VerbalTextFormatterUs {
 public:
  VerbalTextFormatterUsTest(const std::string& country_code,
                          const std::string& state_code)
      : VerbalTextFormatterUs(country_code, state_code) {
  }

  std::string FormInterstateTts(const std::string& source) const{
    return VerbalTextFormatterUs::FormInterstateTts(source);
  }

  std::string FormUsHighwayTts(const std::string& source) const{
    return VerbalTextFormatterUs::FormUsHighwayTts(source);
  }

};

void TryFormInterstateTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.FormInterstateTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormInterstateTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormInterstateTtsString() {
  TryFormInterstateTtsString("I H1", "Interstate H1");
  TryFormInterstateTtsString("I 5", "Interstate 5");
  TryFormInterstateTtsString("I 35", "Interstate 35");
  TryFormInterstateTtsString("I 35E", "Interstate 35E");
  TryFormInterstateTtsString("I 35W", "Interstate 35W");
  TryFormInterstateTtsString("I 95 South", "Interstate 95 South");
  TryFormInterstateTtsString("I 270 Spur", "Interstate 270 Spur");
  TryFormInterstateTtsString("I 495 West", "Interstate 495 West");
  TryFormInterstateTtsString("I-695 West", "Interstate 695 West");
  TryFormInterstateTtsString("I-895", "Interstate 895");
  TryFormInterstateTtsString("i-205 East", "Interstate 205 East");
  TryFormInterstateTtsString("WI 129", "WI 129");
}

void TryFormUsHighwayTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.FormUsHighwayTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormUsHighwayTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormUsHighwayTtsString() {
  TryFormUsHighwayTtsString("US 1", "U.S. 1");
  TryFormUsHighwayTtsString("US 22", "U.S. 22");
  TryFormUsHighwayTtsString("US 220 North", "U.S. 220 North");
  TryFormUsHighwayTtsString("US-220 South", "U.S. 220 South");
  TryFormUsHighwayTtsString("Us 422 Business Alternate", "U.S. 422 Business Alternate");
  TryFormUsHighwayTtsString("Us-522", "U.S. 522");
}

void TryFormat(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.Format(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect Format - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormat() {
  TryFormat("I H1", "Interstate H1");
  TryFormat("I 5", "Interstate 5");
  TryFormat("I 35", "Interstate 35");
  TryFormat("I 35E", "Interstate 35E");
  TryFormat("I 35W", "Interstate 35W");
  TryFormat("I 95 South", "Interstate 95 South");
  TryFormat("I 270 Spur", "Interstate 2 70 Spur");
  TryFormat("I 495 West", "Interstate 4 95 West");
  TryFormat("I-695 West", "Interstate 6 95 West");
  TryFormat("I-895", "Interstate 8 95");
  TryFormat("i-205 East", "Interstate 2 o5 East");

  TryFormat("US 1", "U.S. 1");
  TryFormat("US 22", "U.S. 22");
  TryFormat("US 220 North", "U.S. 2 20 North");
  TryFormat("US-220 South", "U.S. 2 20 South");
  TryFormat("US 202", "U.S. 2 o2");
  TryFormat("Us 422 Business Alternate", "U.S. 4 22 Business Alternate");
  TryFormat("Us-522", "U.S. 5 22");

  TryFormat("PA 23", "PA 23");
  TryFormat("PA 283", "PA 2 83");
  TryFormat("PA 100", "PA 1 hundred");
  TryFormat("PA 1080", "PA 10 80");
  TryFormat("PA 40001", "PA 4 00 o1");
  TryFormat("PA 4007", "PA 40 o7");
  TryFormat("SR 1021", "SR 10 21");
  TryFormat("SR-1021", "SR-10 21");
  TryFormat("Sr 1021", "Sr 10 21");
  TryFormat("T609", "T6 o9");
}

}

int main() {
  test::suite suite("verbal_text_formatter_us");

  // FormInterstateTts
  suite.test(TEST_CASE(TestFormInterstateTtsString));

  // FormUsHighwayTtsString
  suite.test(TEST_CASE(TestFormUsHighwayTtsString));

  // Format
  suite.test(TEST_CASE(TestFormat));

  return suite.tear_down();
}
