import Greeter
import XCTest

final class GreeterTests: XCTestCase {
  func testGreet() { XCTAssertEqual(Greeter().greet("BCR"), "Hello, BCR!") }
}
