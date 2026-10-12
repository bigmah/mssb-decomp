// Prints the CGWindowID of the largest window owned by a process (pid
// argument), for `screencapture -l<id>`. Built by port/tools/run.sh.
import CoreGraphics
import Foundation

let pid = Int32(CommandLine.arguments.count > 1 ? CommandLine.arguments[1] : "0") ?? 0
let list = CGWindowListCopyWindowInfo([.optionAll], kCGNullWindowID) as? [[String: Any]] ?? []
var best = -1
var bestArea = 0.0
for w in list {
    guard let owner = w[kCGWindowOwnerPID as String] as? Int32, owner == pid,
          let layer = w[kCGWindowLayer as String] as? Int, layer == 0,
          let id = w[kCGWindowNumber as String] as? Int,
          let b = w[kCGWindowBounds as String] as? [String: Double] else { continue }
    let area = (b["Width"] ?? 0) * (b["Height"] ?? 0)
    if area > bestArea {
        bestArea = area
        best = id
    }
}
if best < 0 { exit(1) }
print(best)
