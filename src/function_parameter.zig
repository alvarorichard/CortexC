const std = @import("std");
extern "C" fn next() void;



const Token = enum {
    Int,
    Char,
    Mul,
    Id,
    Comma,
    RParen,
    Loc,
};

const Identifier = struct {
    class: Token,
    bclass: Token,
    btype: Token,
    bvalue: i32,
    type_: Token,
    value: i32,
};

var token: Token = undefined;
var line: i32 = undefined;
var currentId: Identifier = undefined;
var index_of_bp: i32 = undefined;

export fn functionParameter() i32 {
    var params: i32 = 0;
    var type_: Token = .Int;

    while (token != .RParen) {
        type_ = .Int;
        if (token == .Int) {
            if (match(.Int) != 0) { return -1; }
        } else if (token == .Char) {
            type_ = .Char;
            if (match(.Char) != 0) { return -1; }
        }

        while (token == .Mul) {
            if (match(.Mul) != 0) { return -1; }
            type_ = .Mul;
        }

        if (token != .Id) {
            std.debug.print("{}: bad parameter declaration\n", .{line});
            return -1;
        }
        if (currentId.class == .Loc) {
            std.debug.print("{}: duplicate parameter declaration\n", .{line});
            return -1;
        }

        if (match(.Id) != 0) { return -1; }

        currentId.bclass = currentId.class;
        currentId.class = .Loc;
        currentId.btype = currentId.type_;
        currentId.type_ = type_;
        currentId.bvalue = currentId.value;
        currentId.value = params;
        params += 1;

        if (token == .Comma) {
            if (match(.Comma) != 0) { return -1; }
        }
    }

    index_of_bp = params + 1;
    return 0;
}

fn match(expectedToken: Token) i32 {
    if (token != expectedToken) {
        std.debug.print("expected token: {}, got: {}\n", .{expectedToken, token});
        return -1;
    }
    next();
    return 0;
}
