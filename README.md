# getmeout - Stack based language

```
push 5
push 1
sub
push 4
isequal if
        push 32
        pprint
end

push 33
sub
push 4
isequal if
        push 41
        pprint
        exit 0
end


push -1
pprint
exit 0
```
`Output:`
```
32
-1
```