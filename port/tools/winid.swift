// Prints the CGWindowID of the first on-screen window owned by a process
// (pid argument), for `screencapture -l<id>`. Built by port/tools/run.sh.
import CoreGraphics
import Foundation

let pid = Int32(CommandLine.arguments.count > 1 ? CommandLine.arguments[1] : "0") ?? 0
let list = CGWindowListCopyWindowInfo([.optionAll], kCGNullWindowID) as? [[String: Any]] ?? []
for w in list {
    if let owner = w[kCGWindowOwnerPID as String] as? Int32, owner == pid,
       let layer = w[kCGWindowLayer as String] as? Int, layer == 0,
       let id = w[kCGWindowNumber as String] as? Int {
        print(id)
        exit(0)
    }
}
exit(1)
