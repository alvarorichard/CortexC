const std = @import("std");

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

fn functionParameter() !void {
    var params: i32 = 0;
    var type_: Token = .Int;

    while (token != .RParen) {
        type_ = .Int;
        if (token == .Int) {
            try match(.Int);
        } else if (token == .Char) {
            type_ = .Char;
            try match(.Char);
        }

        while (token == .Mul) {
            try match(.Mul);
            type_ = .Mul;
        }

        if (token != .Id) {
            std.debug.print("{}: bad parameter declaration\n", .{line});
            return error.BadParameterDeclaration;
        }
        if (currentId.class == .Loc) {
            std.debug.print("{}: duplicate parameter declaration\n", .{line});
            return error.DuplicateParameterDeclaration;
        }

        try match(.Id);

        currentId.bclass = currentId.class;
        currentId.class = .Loc;
        currentId.btype = currentId.type_;
        currentId.type_ = type_;
        currentId.bvalue = currentId.value;
        currentId.value = params;
        params += 1;

        if (token == .Comma) {
            try match(.Comma);
        }
    }

    index_of_bp = params + 1;
}

fn match(expectedToken: Token) !void {
    if (token != expectedToken) {
        std.debug.print("expected token: {}, got: {}\n", .{expectedToken, token});
        return error.TokenMismatch;
    }
    next();
}

fn next() void {
    // Implementação da função next
}
